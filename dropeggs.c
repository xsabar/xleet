#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

// 仅针对2个鸡蛋的情况
int dropeggs_math_two(int floors) {
    return ceil((sqrt(floors * 8 + 1) - 1) / 2);
}

/**
 * @brief O(mn2)动态规划算法
 * m-鸡蛋数，n-楼层数，dp[m][n]-扔鸡蛋次数
 * dp[m][n] = min{max{dp[m-1][j-1],dp[m][n-j]}+1 | 1<=j<=n}
 */
int dropeggs_dpmn2(int eggs, int floors) {
    int dp[2][floors + 1];
    int prev_idx = 0;
    int curr_idx = 1;
    memset(dp, 0, sizeof(dp));
    // 1个鸡蛋时扔鸡蛋的次数
    for (int i = 0; i <= floors; i++) {
        dp[0][i] = i;
    }
    // 2个以上鸡蛋时扔鸡蛋的次数
    for (int i = 2; i <= eggs; i++) {
        for (int j = 1; j <= floors; j++) {
            int min = INT_MAX;
            for (int k = 1; k <= j; k++) {
                int x = max(dp[prev_idx][k - 1], dp[curr_idx][j - k]) + 1;
                if (min > x) {
                    min = x;
                }
            }
            dp[curr_idx][j] = min;
        }
        prev_idx = 1 - prev_idx;
        curr_idx = 1 - curr_idx;
    }
    return dp[prev_idx][floors];
}

/**
 * @brief O(mnlogn)动态规划算法
 * m-鸡蛋数，n-楼层数，dp[m][n]-扔鸡蛋次数
 * dp[m][n] = min{max{dp[m-1][j-1],dp[m][n-j]}+1 | 1<=j<=n}
 */
int dropeggs_dpmnlogn(int eggs, int floors) {
    int dp[2][floors + 1];
    int prev_idx = 0;
    int curr_idx = 1;
    memset(dp, 0, sizeof(dp));
    // 1个鸡蛋时扔鸡蛋的次数
    for (int i = 0; i <= floors; i++) {
        dp[0][i] = i;
    }
    // 2个以上鸡蛋时扔鸡蛋的次数
    for (int i = 2; i <= eggs; i++) {
        dp[curr_idx][1] = 1;
        for (int j = 1; j <= floors; j++) {
            int left = 1;
            int right = j;
            // 二分查找，找到临界楼层
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (dp[prev_idx][mid - 1] < dp[curr_idx][j - mid]) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            dp[curr_idx][j] = min(
                max(dp[prev_idx][left - 1], dp[curr_idx][j - left]) + 1,
                max(dp[prev_idx][right - 1], dp[curr_idx][j - right]) + 1
            );
        }
        prev_idx = 1 - prev_idx;
        curr_idx = 1 - curr_idx;
    }
    return dp[prev_idx][floors];
}

/**
 * @brief O(mn)动态规划算法
 * m-鸡蛋数，n-楼层数，dp[m][n]-扔鸡蛋次数
 * dp[m][n] = min{
 *     max{dp[m-1][k-1],dp[m][n-k]}+1,
 *     max{dp[m-1][k],dp[m][n-k-1]}+1
 *     | k=n-1层楼时第一次扔鸡蛋的楼层 
 * }
 */
int dropeggs_dpmn(int eggs, int floors) {
    int dp[2][floors + 1];
    int prev_idx = 0;
    int curr_idx = 1;
    memset(dp, 0, sizeof(dp));
    // 1个鸡蛋时扔鸡蛋的次数
    for (int i = 0; i <= floors; i++) {
        dp[0][i] = i;
    }
    // 2个以上鸡蛋时扔鸡蛋的次数
    for (int i = 2; i <= eggs; i++) {
        int start = 1; // 开始仍鸡蛋的楼层
        dp[curr_idx][1] = 1;
        for (int j = 2; j <= floors; j++) {
            // 贪心选择，最优解在当前楼层和下一楼层中产生
            int min = max(dp[prev_idx][start - 1], dp[curr_idx][j - start]) + 1;
            int x = max(dp[prev_idx][start], dp[curr_idx][j - start - 1]) + 1;
            if (min > x) {
                min = x;
                ++start;
            }
            dp[curr_idx][j] = min;
        }
        prev_idx = 1 - prev_idx;
        curr_idx = 1 - curr_idx;
    }
    return dp[prev_idx][floors];
}

/**
 * @brief O(mn)动态规划算法
 * m-鸡蛋数，n-扔蛋次数，dp[m][n]-楼层数
 * dp[m][n]=dp[m-1][n-1]+dp[m][n-1]+1
 * @param eggs 
 * @param floors 
 * @return int 
 */
int dropeggs_dpdrop(int eggs, int floors) {
    int dp[2][floors + 1];
    int prev_idx = 0;
    int curr_idx = 1;
    int drop_cnt = floors;
    memset(dp, 0, sizeof(dp));
    // 1个鸡蛋时扔k次能测试的最大楼层数
    for (int i = 0; i <= floors; i++) {
        dp[0][i] = i;
    }
    // 2个以上鸡蛋扔k次能测试的最大楼层数
    for (int i = 2; i <= eggs; i++) {
        drop_cnt = 0;
        do {
            ++drop_cnt;
            dp[curr_idx][drop_cnt] = dp[prev_idx][drop_cnt - 1] + dp[curr_idx][drop_cnt - 1] + 1;
        } while (dp[curr_idx][drop_cnt] < floors);
        prev_idx = 1 - prev_idx;
        curr_idx = 1 - curr_idx;
    }
    return drop_cnt;
}

int main(int argc, char* argv[]) {
    int eggs = 0;   // 鸡蛋数
    int floors = 0; // 楼层数
    if (argc >= 3) {
        eggs = atoi(argv[1]);
        floors = atoi(argv[2]);
    } else {
        eggs = 2;
        floors = 100;
    }
    if (eggs == 2) {
        printf("dropeggs_math_two: %d\n", dropeggs_math_two(floors));
    }
    printf("dropeggs_dpmn2: %d\n", dropeggs_dpmn2(eggs, floors));
    printf("dropeggs_dpmnlogn: %d\n",dropeggs_dpmnlogn(eggs, floors));
    printf("dropeggs_dpmn: %d\n", dropeggs_dpmn(eggs, floors));
    printf("dropeggs_dpdrop: %d\n", dropeggs_dpdrop(eggs, floors));
    return 0;
}