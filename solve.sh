#!/bin/bash

if [ -z "$1" ]; then
    echo "❌ 파일 경로가 없습니다."
    exit 1
fi

find . -type f -not -name "*.*" -perm +111 -delete

FILENAME=$(basename "$1")
RAW_ID=$(echo "$FILENAME" | sed -E 's/.*p([0-9]+)\.cpp/\1/')
PROBLEM_ID=$((10#$RAW_ID))

if [[ ! "$PROBLEM_ID" =~ ^[0-9]+$ ]]; then
    echo "❌ ERROR: 유효하지 않은 파일 형식입니다 ($FILENAME)"
    exit 1
fi

echo "🌐 문제 정보를 가져오는 중..."
PROBLEM_NAME=$(curl -s "https://solved.ac/api/v3/problem/show?problemId=$PROBLEM_ID" \
    | grep -oE '"titleKo":"[^"]+"' \
    | cut -d'"' -f4)

if [ -z "$PROBLEM_NAME" ]; then
    PROBLEM_NAME="알 수 없는 문제"
fi

git add "$1"
git commit -m "solve $PROBLEM_ID: $PROBLEM_NAME (https://www.acmicpc.net/problem/$PROBLEM_ID)"

echo "✅ $FILENAME ($PROBLEM_NAME) 커밋 완료!"
