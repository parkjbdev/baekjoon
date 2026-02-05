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

USER_DATA=$(curl -s "https://solved.ac/api/v3/user/show?handle=parkjbdev")
TIER_NUM=$(echo "$USER_DATA" | grep -oE '"tier":[0-9]+' | cut -d: -f2)
SOLVED_COUNT=$(echo "$USER_DATA" | grep -oE '"solvedCount":[0-9]+' | cut -d: -f2)
RATING=$(echo "$USER_DATA" | grep -oE '"rating":[0-9]+' | cut -d: -f2)
RANK=$(echo "$USER_DATA" | grep -oE '"rank":[0-9]+' | cut -d: -f2)

get_tier_name() {
    local t=$1
    if [ $t -eq 0 ]; then echo "⚪ Unranked"; return; fi

    # 등급별 접두사 및 이모티콘 설정
    local prefixes=("B" "S" "G" "P" "D" "R")
    local icons=("🥉" "🥈" "🥇" "✨" "💎" "♦️") # 브론즈, 실버, 골드, 플래티넘, 다이아, 루비

    if [ $t -ge 31 ]; then
        echo "🌈 Master"
    else
        local idx=$(( (t - 1) / 5 ))    # 0:Bronze, 1:Silver ...
        local sub=$(( 5 - (t - 1) % 5 )) # 5, 4, 3, 2, 1

        echo "${icons[$idx]} ${prefixes[$idx]}$sub"
    fi
}
TIER_NAME=$(get_tier_name $TIER_NUM)

echo "📊 현재 상태: $TIER_NAME ($RATING) | $SOLVED_COUNT 문제 해결 | ${RANK}위"
