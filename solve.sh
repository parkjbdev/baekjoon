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

get_tier_icon() {
    local t=$1
    if [ $t -eq 0 ]; then echo "⚪"; return; fi

    local icons=("🥉" "🥈" "🥇" "✨" "💎" "♦️") # 브론즈, 실버, 골드, 플래티넘, 다이아, 루비

    if [ $t -ge 31 ]; then
        echo "🌈"
    else
        local idx=$(( (t - 1) / 5 ))    # 0:Bronze, 1:Silver ...
        echo "${icons[$idx]}"
    fi
}

get_tier_name() {
    local t=$1
    if [ $t -eq 0 ]; then echo "Unranked"; return; fi

    local prefixes=("B" "S" "G" "P" "D" "R")

    if [ $t -ge 31 ]; then
        echo "Master"
    else
        local idx=$(( (t - 1) / 5 ))    # 0:Bronze, 1:Silver ...
        local sub=$(( 5 - (t - 1) % 5 )) # 5, 4, 3, 2, 1

        echo "${prefixes[$idx]}$sub"
    fi
}

calculate_next_goal() {
    local current_rating=$1
    local t=$2

    local cutoffs=(0 30 60 90 120 150 200 300 400 500 650 800 950 1100 1250 1400 1600 1750 1900 2000 2100 2200 2300 2400 2500 2600 2700 2800 2850 2900 2950 3000)

    if [ $t -lt 31 ]; then
        local next_tier_num=$((t + 1))
        local next_name=$(get_tier_name $next_tier_num)
        local next_cutoff=${cutoffs[$next_tier_num]}
        local diff=$((next_cutoff - current_rating))

        echo "$next_name -$diff"
    fi
}

TIER_ICON=$(get_tier_icon $TIER_NUM)
TIER_NAME=$(get_tier_name $TIER_NUM)

NEXT_GOAL_TEXT=$(calculate_next_goal $RATING $TIER_NUM)

#echo "📊 현재 상태: ${TIER_ICON} ${TIER_NAME} ($RATING) ${NEXT_GOAL_TEXT} | $SOLVED_COUNT 문제 해결 | ${RANK}위"
# 색상 및 스타일 정의
BOLD='\033[1m'
REVERSE='\033[7m'
RESET='\033[0m'

# 티어별 색상 정의
case $(( (TIER_NUM - 1) / 5 )) in
    0) COLOR='\033[38;5;172m' ;; # Bronze
    1) COLOR='\033[38;5;246m' ;; # Silver
    2) COLOR='\033[38;5;220m' ;; # Gold
    3) COLOR='\033[38;5;48m'  ;; # Platinum
    4) COLOR='\033[38;5;39m'  ;; # Diamond
    5) COLOR='\033[38;5;197m' ;; # Ruby
    *) COLOR='\033[38;5;205m' ;; # Master/Unranked
esac

# 목표 텍스트 분리 (예: "G4 -15")
NEXT_TIER=$(echo $NEXT_GOAL_TEXT | cut -d' ' -f1)
DIFF=$(echo $NEXT_GOAL_TEXT | cut -d' ' -f2)

echo -e "\n${BOLD}${REVERSE}  📊 SOLVED.AC DASHBOARD  ${RESET}"
echo -e "${COLOR}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
echo -e "  ${TIER_ICON} ${BOLD}${TIER_NAME}${RESET} (${RATING})"
echo -e "  🚩 다음 목표: ${BOLD}${NEXT_TIER}${RESET} (현재 ${DIFF}점)"
echo -e "  ✅ 해결한 문제: ${BOLD}${SOLVED_COUNT}${RESET}개"
echo -e "  🏆 현재 순위: ${BOLD}${RANK}${RESET}위"
echo -e "${COLOR}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"