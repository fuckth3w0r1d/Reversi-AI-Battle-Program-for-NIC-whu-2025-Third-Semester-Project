/***
 *               ii.                                         ;9ABH,          
 *              SA391,                                    .r9GG35&G          
 *              &#ii13Gh;                               i3X31i;:,rB1         
 *              iMs,:,i5895,                         .5G91:,:;:s1:8A         
 *               33::::,,;5G5,                     ,58Si,,:::,sHX;iH1        
 *                Sr.,:;rs13BBX35hh11511h5Shhh5S3GAXS:.,,::,,1AG3i,GG        
 *                .G51S511sr;;iiiishS8G89Shsrrsh59S;.,,,,,..5A85Si,h8        
 *               :SB9s:,............................,,,.,,,SASh53h,1G.       
 *            .r18S;..,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....,,.1H315199,rX,       
 *          ;S89s,..,,,,,,,,,,,,,,,,,,,,,,,....,,.......,,,;r1ShS8,;Xi       
 *        i55s:.........,,,,,,,,,,,,,,,,.,,,......,.....,,....r9&5.:X1       
 *       59;.....,.     .,,,,,,,,,,,...        .............,..:1;.:&s       
 *      s8,..;53S5S3s.   .,,,,,,,.,..      i15S5h1:.........,,,..,,:99       
 *      93.:39s:rSGB@A;  ..,,,,.....    .SG3hhh9G&BGi..,,,,,,,,,,,,.,83      
 *      G5.G8  9#@@@@@X. .,,,,,,.....  iA9,.S&B###@@Mr...,,,,,,,,..,.;Xh     
 *      Gs.X8 S@@@@@@@B:..,,,,,,,,,,. rA1 ,A@@@@@@@@@H:........,,,,,,.iX:    
 *     ;9. ,8A#@@@@@@#5,.,,,,,,,,,... 9A. 8@@@@@@@@@@M;    ....,,,,,,,,S8    
 *     X3    iS8XAHH8s.,,,,,,,,,,...,..58hH@@@@@@@@@Hs       ...,,,,,,,:Gs   
 *    r8,        ,,,...,,,,,,,,,,.....  ,h8XABMMHX3r.          .,,,,,,,.rX:  
 *   :9, .    .:,..,:;;;::,.,,,,,..          .,,.               ..,,,,,,.59  
 *  .Si      ,:.i8HBMMMMMB&5,....                    .            .,,,,,.sMr
 *  SS       :: h@@@@@@@@@@#; .                     ...  .         ..,,,,iM5
 *  91  .    ;:.,1&@@@@@@MXs.                            .          .,,:,:&S
 *  hS ....  .:;,,,i3MMS1;..,..... .  .     ...                     ..,:,.99
 *  ,8; ..... .,:,..,8Ms:;,,,...                                     .,::.83
 *   s&: ....  .sS553B@@HX3s;,.    .,;13h.                            .:::&1
 *    SXr  .  ...;s3G99XA&X88Shss11155hi.                             ,;:h&,
 *     iH8:  . ..   ,;iiii;,::,,,,,.                                 .;irHA  
 *      ,8X5;   .     .......                                       ,;iihS8Gi
 *         1831,                                                 .,;irrrrrs&@
 *           ;5A8r.                                            .:;iiiiirrss1H
 *             :X@H3s.......                                .,:;iii;iiiiirsrh
 *              r#h:;,...,,.. .,,:;;;;;:::,...              .:;;;;;;iiiirrss1
 *             ,M8 ..,....,.....,,::::::,,...         .     .,;;;iiiiiirss11h
 *             8B;.,,,,,,,.,.....          .           ..   .:;;;;iirrsss111h
 *            i@5,:::,,,,,,,,.... .                   . .:::;;;;;irrrss111111
 *            9Bi,:,,,,......                        ..r91;;;;;iirrsss1ss1111
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "../include/playerbase.h"

#define ME 'O'    // 我方棋子标识
#define OP 'o'    // 对方棋子标识
#define MAXSIZE 12 // 最大棋盘尺寸
//#define SEARCH_DEPTH_10 4  
//#define SEARCH_DEPTH_12 4  
//#define SEARCH_DEPTH_8 5  全部改用动态权重

// 各尺寸棋盘的权重表
const int pos8_weights[8][8] = {
    {1200, -200,  200,   50,   50,  200, -200, 1200},
    {-200, -400,  -50,  -50,  -50,  -50, -400, -200},
    { 200,  -50,  25,   6,   6,  25,  -50,  200},
    {  50,  -50,   6,   3,   3,   6,  -50,   50},
    {  50,  -50,   6,   3,   3,   6,  -50,   50},
    { 200,  -50,  25,   6,   6,  25,  -50,  200},
    {-200, -400,  -50,  -50,  -50,  -50, -400, -200},
    {1200, -200,  200,   50,   50,  200, -200, 1200}
};

const int pos10_weights[10][10]={     
    {1500, -300,  300,  100,   50,   50,  100,  300, -300, 1500},
    {-300, -500, -100,  -80,  -80,  -80,  -80, -100, -500, -300},
    { 300, -100,  50,  10,   5,   5,  10,  50, -100,  300},
    { 100,  -80,  10,   5,   3,   3,   5,  10,  -80,  100},
    {  50,  -80,   5,   3,   1,   1,   3,   5,  -80,   50},
    {  50,  -80,   5,   3,   1,   1,   3,   5,  -80,   50},
    { 100,  -80,  10,   5,   3,   3,   5,  10,  -80,  100},
    { 300, -100,  50,  10,   5,   5,  10,  50, -100,  300},
    {-300, -500, -100,  -80,  -80,  -80,  -80, -100, -500, -300},
    {1500, -300,  300,  100,   50,   50,  100,  300, -300, 1500}
};

const int pos12_weights[12][12]={     
    {2000, -400,  40,  150,  100,   80,   80,  100,  150,  40, -400, 2000},
    {-400, -600, -150, -120, -100, -100, -100, -100, -120, -150, -600, -400},
    { 40, -150,  50,  25,   8,   6,   6,   8,  25,  50, -150,  40},
    { 150, -120,  25,   8,   5,   4,   4,   5,   8,  25, -120,  150},
    { 100, -100,   8,   5,   3,   2,   2,   3,   5,   8, -100,  100},
    {  80, -100,   6,   4,   2,   1,   1,   2,   4,   6, -100,   80},
    {  80, -100,   6,   4,   2,   1,   1,   2,   4,   6, -100,   80},
    { 100, -100,   8,   5,   3,   2,   2,   3,   5,   8, -100,  100},
    { 150, -120,  25,   8,   5,   4,   4,   5,   8,  25, -120,  150},
    { 40, -150,   50,  25,   8,   6,   6,   8,  25,  50, -150,  40},
    {-400, -600, -150, -120, -100, -100, -100, -100, -120, -150, -600, -400},
    {2000, -400,  40,  150,  100,   80,   80,  100,  150,  40, -400, 2000}
};

// 8个方向的移动向量
const int dirs[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// 落子策略结构
typedef struct
{
    int places[MAXSIZE*MAXSIZE];
    int count;
} strategy;

// 8x8专用函数和结构
typedef struct {
    int positions[64];  // 合法落子的索引
    int count;          // 合法落子数量
} Strategy_8;

// 8x8专用辅助函数
static inline int pos_to_idx_8(int x, int y) { return x * 8 + y; }
static inline int idx_to_x_8(int idx) { return idx / 8; }
static inline int idx_to_y_8(int idx) { return idx % 8; }
static inline bool in_board_8(int x, int y) { return (x >= 0 && x < 8 && y >= 0 && y < 8); }

// 检查8x8棋盘我方是否可以在该位置落子
static bool is_valid_place_me_8(uint64_t me, uint64_t op, int idx) {
    int x = idx_to_x_8(idx);
    int y = idx_to_y_8(idx);
    if (!in_board_8(x, y)) return false;

    uint64_t mask = 1ULL << idx;
    if ((me & mask) || (op & mask)) return false;

    for (int d = 0; d < 8; d++) {
        int dx = dirs[d][0];
        int dy = dirs[d][1];
        int nx = x + dx;
        int ny = y + dy;
        
        if (!in_board_8(nx, ny)) continue;
        
        uint64_t first_step = 1ULL << pos_to_idx_8(nx, ny);
        if (!(op & first_step)) continue;
        
        bool found_me = false;
        while (1) {
            nx += dx;
            ny += dy;
            if (!in_board_8(nx, ny)) break;
            
            uint64_t current = 1ULL << pos_to_idx_8(nx, ny);
            if (me & current) {
                found_me = true;
                break;
            }
            if (!(op & current)) break;
        }
        
        if (found_me) return true;
    }
    
    return false;
}

// 检查8x8棋盘对方是否可以在该位置落子
static bool is_valid_place_op_8(uint64_t me, uint64_t op, int idx) {
    int x = idx_to_x_8(idx);
    int y = idx_to_y_8(idx);
    if (!in_board_8(x, y)) return false;

    uint64_t mask = 1ULL << idx;
    if ((me & mask) || (op & mask)) return false;

    for (int d = 0; d < 8; d++) {
        int dx = dirs[d][0];
        int dy = dirs[d][1];
        int nx = x + dx;
        int ny = y + dy;
        
        if (!in_board_8(nx, ny)) continue;
        
        uint64_t first_step = 1ULL << pos_to_idx_8(nx, ny);
        if (!(me & first_step)) continue;
        
        bool found_op = false;
        while (1) {
            nx += dx;
            ny += dy;
            if (!in_board_8(nx, ny)) break;
            
            uint64_t current = 1ULL << pos_to_idx_8(nx, ny);
            if (op & current) {
                found_op = true;
                break;
            }
            if (!(me & current)) break;
        }
        
        if (found_op) return true;
    }
    
    return false;
}

//生成8x8我方所有合法落子
static void init_strategy_me_8(uint64_t me, uint64_t op, Strategy_8* strat) {
    strat->count = 0;
    for (int idx = 0; idx < 64; idx++) {
        if (is_valid_place_me_8(me, op, idx)) {
            strat->positions[strat->count++] = idx;
        }
    }
}

//生成8x8对方所有合法落子
static void init_strategy_op_8(uint64_t me, uint64_t op, Strategy_8* strat) {
    strat->count = 0;
    for (int idx = 0; idx < 64; idx++) {
        if (is_valid_place_op_8(me, op, idx)) {
            strat->positions[strat->count++] = idx;
        }
    }
}

// 在8x8棋盘上执行我方落子
static void make_place_me_8(uint64_t me, uint64_t op, int idx, uint64_t* new_me, uint64_t* new_op) {
    *new_me = me | (1ULL << idx);
    *new_op = op;
    
    int x = idx_to_x_8(idx);
    int y = idx_to_y_8(idx);
    
    for (int d = 0; d < 8; d++) {
        int dx = dirs[d][0];
        int dy = dirs[d][1];
        int nx = x + dx;
        int ny = y + dy;
        
        if (!in_board_8(nx, ny)) continue;
        
        uint64_t first_step = 1ULL << pos_to_idx_8(nx, ny);
        if (!(op & first_step)) continue;
        
        uint64_t flip_mask = first_step;
        bool found_me = false;
        
        while (1) {
            nx += dx;
            ny += dy;
            if (!in_board_8(nx, ny)) break;
            
            uint64_t current = 1ULL << pos_to_idx_8(nx, ny);
            if (me & current) {
                found_me = true;
                break;
            }
            if (!(op & current)) break;
            
            flip_mask |= current;
        }
        
        if (found_me) {
            *new_me |= flip_mask;
            *new_op &= ~flip_mask;
        }
    }
}

// 在8x8棋盘上执行对方落子
static void make_place_op_8(uint64_t me, uint64_t op, int idx, uint64_t* new_me, uint64_t* new_op) {
    *new_op = op | (1ULL << idx);
    *new_me = me;
    
    int x = idx_to_x_8(idx);
    int y = idx_to_y_8(idx);
    
    for (int d = 0; d < 8; d++) {
        int dx = dirs[d][0];
        int dy = dirs[d][1];
        int nx = x + dx;
        int ny = y + dy;
        
        if (!in_board_8(nx, ny)) continue;
        
        uint64_t first_step = 1ULL << pos_to_idx_8(nx, ny);
        if (!(me & first_step)) continue;
        
        uint64_t flip_mask = first_step;
        bool found_op = false;
        
        while (1) {
            nx += dx;
            ny += dy;
            if (!in_board_8(nx, ny)) break;
            
            uint64_t current = 1ULL << pos_to_idx_8(nx, ny);
            if (op & current) {
                found_op = true;
                break;
            }
            if (!(me & current)) break;
            
            flip_mask |= current;
        }
        
        if (found_op) {
            *new_op |= flip_mask;
            *new_me &= ~flip_mask;
        }
    }
}

// 8x8棋盘评估函数
static int evaluate_8(uint64_t me, uint64_t op) {
    int score = 0;

    int mob_diff_8=0;
    int count_diff_8=0;
    int stab_diff_8=0;

    int empty_count_8=0;
    int total_8=64;

    int early_threshold = total_8 * 0.8;     // 起手
    int early_mid_threshold = total_8 * 0.5;  // 开局：空格大于棋盘格子的一半
    int mid_threshold = total_8 * 0.25;     // 中局：空格介于1/4到1/2之间

    for (int idx = 0; idx < 64; idx++) {
        if (is_valid_place_op_8(me, op, idx)) {
            mob_diff_8--;
        }
        if (is_valid_place_me_8(me, op, idx)) {
            mob_diff_8++;
        }
        
        int x = idx_to_x_8(idx);
        int y = idx_to_y_8(idx);
        if (me & (1ULL << idx)) {
            stab_diff_8 += pos8_weights[x][y];
            count_diff_8++;
        } else if (op & (1ULL << idx)) {
            stab_diff_8 -= pos8_weights[x][y];
            count_diff_8--;
        }else {
            empty_count_8++;
        }
    }

    double stability_weight_8=0;
    double mobility_weight_8=0;
    double count_weight_8=0;

    if (empty_count_8 > early_threshold) {
        // 起手阶段：
        mobility_weight_8 =  1.0;
        stability_weight_8 = 0.1* 0;
        count_weight_8 = 0;
    } else if (empty_count_8 > early_mid_threshold) {
        // 开局阶段：
        mobility_weight_8 =  1.0;
        stability_weight_8 = 0.1* 0.5;
        count_weight_8 = 0.3;
    } else if (empty_count_8 > mid_threshold) {
        // 中局阶段：
        mobility_weight_8 = 0.5;
        stability_weight_8 = 0.1* 1.5;
        count_weight_8 = 0.5;
    }else {  // 残局局阶段：
        mobility_weight_8 = 0.1;
        stability_weight_8 = 0.1* 0.5;
        count_weight_8 = 1.2;
    }

    score += mob_diff_8 * mobility_weight_8;
    score += count_diff_8 * count_weight_8;
    score += stab_diff_8 * stability_weight_8;

    return score;
}

// 根据空格数量动态计算搜索深度
int get_dynamic_search_depth_8(uint64_t me, uint64_t op) {
    // 8×8棋盘总格子数
    const int TOTAL_CELLS = 64;
    int empty_count_8=0;

    bool board_flag_8=true;

    for (int idx = 0; idx < 64; idx++) {
        board_flag_8 = (me & (1ULL << idx)) && (op & (1ULL << idx));
        if(!board_flag_8) empty_count_8++;
    }

    // 定义不同阶段的搜索深度
    if (empty_count_8 > TOTAL_CELLS * 0.75) {
        // 开局阶段 (空格>48)：浅搜索
        return 4;
    } else if (empty_count_8 > TOTAL_CELLS * 0.5) {
        // 中局阶段 (空格>32)：中等搜索
        return 6;
    } else if (empty_count_8 > TOTAL_CELLS * 0.25) {
        // 中残局阶段 (空格>16)：较深搜索
        return 8;
    } else if (empty_count_8 > 8) {
        // 残局阶段 (空格>8)：深搜索
        return 10;
    } else {
        // 终局阶段：最大搜索深度
        return 14;
    }
}

// 8x8专用alpha-beta剪枝
static int alphabeta_8(uint64_t me, uint64_t op, int depth, int alpha, int beta, bool is_max) {
    if (depth == 0) {
        return evaluate_8(me, op);
    }

    Strategy_8 moves;
    if (is_max) {
        init_strategy_me_8(me, op, &moves);
        if (moves.count == 0) {
            init_strategy_op_8(me, op, &moves);
            if (moves.count == 0) {
                return evaluate_8(me, op);
            }
            return alphabeta_8(me, op, depth - 1, alpha, beta, false);
        }

        int max_val = -1000000;
        for (int i = 0; i < moves.count; i++) {
            uint64_t new_me, new_op;
            make_place_me_8(me, op, moves.positions[i], &new_me, &new_op);
            int val = alphabeta_8(new_me, new_op, depth - 1, alpha, beta, false);
            if (val > max_val) max_val = val;
            if (val > alpha) alpha = val;
            if (beta <= alpha) break;
        }
        return max_val;
    } else {
        init_strategy_op_8(me, op, &moves);
        if (moves.count == 0) {
            init_strategy_me_8(me, op, &moves);
            if (moves.count == 0) {
                return evaluate_8(me, op);
            }
            return alphabeta_8(me, op, depth - 1, alpha, beta, true);
        }

        int min_val = 1000000;
        for (int i = 0; i < moves.count; i++) {
            uint64_t new_me, new_op;
            make_place_op_8(me, op, moves.positions[i], &new_me, &new_op);
            int val = alphabeta_8(new_me, new_op, depth - 1, alpha, beta, true);
            if (val < min_val) min_val = val;
            if (val < beta) beta = val;
            if (beta <= alpha) break;
        }
        return min_val;
    }
}



// 以下为 10*10 与 12*12 棋盘所用函数
// 棋盘位置检查
bool in_board(struct Player *player,int x,int y) {
    return (x>=0 && x<player->row_cnt && y>=0 && y<player->col_cnt);
}

// 检查是否可以进行翻转
bool can_flip(char** board,struct Player *player,int x,int y,int dx,int dy) {
    int nx=x+dx;
    int ny=y+dy;
    bool findop=false;
    while(in_board(player,nx,ny) && board[nx][ny]==OP) {
        findop=true;
        nx+=dx;
        ny+=dy;
    }
    return in_board(player,nx,ny) && board[nx][ny]==ME && findop;
}

// 检查我方是否可以在该位置落子
bool is_valid_place(char** board,struct Player *player,int x,int y) {
    if(!in_board(player,x,y)) return false;
    if(board[x][y]==OP || board[x][y]==ME) return false;
    for(int i=0;i<8;i++) {
        if(can_flip(board,player,x,y,dirs[i][0],dirs[i][1])) return true;
    }
    return false;
}

// 检查对方是否可以翻转
bool can_flip_opponent(char** board,struct Player *player,int x,int y,int dx,int dy) {
    int nx=x+dx;
    int ny=y+dy;
    bool findme=false;
    while(in_board(player,nx,ny) && board[nx][ny]==ME) {
        findme=true;
        nx+=dx;
        ny+=dy;
    }
    return in_board(player,nx,ny) && board[nx][ny]==OP && findme;
}

// 检查对方是否可以在该位置落子
bool is_valid_place_opponent(char** board,struct Player *player,int x,int y) {
    if(!in_board(player,x,y)) return false;
    if(board[x][y]==OP || board[x][y]==ME) return false;
    for(int i=0;i<8;i++) {
        if(can_flip_opponent(board,player,x,y,dirs[i][0],dirs[i][1])) return true;
    }
    return false;
}

// 复制棋盘
char** cpy_board(struct Player *player,char** srcboard) {
    char** desboard=(char**)malloc(player->row_cnt*sizeof(char*));
    for(int i=0;i<player->row_cnt;i++) {
        desboard[i]=(char*)malloc(player->col_cnt*sizeof(char));
        memcpy(desboard[i], srcboard[i], player->col_cnt*sizeof(char));
    }
    return desboard;
}

// 释放棋盘内存
void free_board(struct Player *player, char** board) {
    for(int i=0;i<player->row_cnt;i++) {
        free(board[i]);
    }
    free(board);
}

// 执行翻转操作
void flip(char** board,struct Player *player,int x,int y,int dx,int dy) {
    int nx=x+dx;
    int ny=y+dy;
    while(board[nx][ny]==OP && in_board(player,nx,ny)) {
        board[nx][ny]=ME;
        nx+=dx;
        ny+=dy;
    }
}

// 执行我方落子操作
void make_place(char** board,struct Player *player,int x,int y) {
    board[x][y] = ME;
    for (int i = 0; i < 8; i++) {
        if (can_flip(board,player,x,y,dirs[i][0],dirs[i][1])) {
            flip(board,player,x,y,dirs[i][0],dirs[i][1]);
        }
    }
}

// 执行对方翻转操作
void flip_opponent(char** board,struct Player *player,int x,int y,int dx,int dy) {
    int nx=x+dx;
    int ny=y+dy;
    while(board[nx][ny]==ME && in_board(player,nx,ny)) {
        board[nx][ny]=OP;
        nx+=dx;
        ny+=dy;
    }
}

// 执行对方落子操作
void make_place_opponent(char** board,struct Player *player,int x,int y) {
    board[x][y] = OP;
    for (int i = 0; i < 8; i++) {
        if (can_flip_opponent(board,player,x,y,dirs[i][0],dirs[i][1])) {
            flip_opponent(board,player,x,y,dirs[i][0],dirs[i][1]);
        }
    }
}

// 初始化我方落子策略
void init_strategy(char** board,struct Player *player,strategy* s) {
    s->count=0;
    for(int i=player->row_cnt-1;i>=0;i--) {
        for(int j=player->row_cnt-1;j>=0;j--) {
            if(is_valid_place(board,player,i,j)) {
                s->places[s->count]=i*player->row_cnt+j; 
                s->count++;
            }
        }
    }
}

// 初始化对方落子策略
void init_strategy_opponent(char** board,struct Player *player,strategy* s) {
    s->count=0;
    for(int i=player->row_cnt-1;i>=0;i--) {
        for(int j=player->row_cnt-1;j>=0;j--) {
            if(is_valid_place_opponent(board,player,i,j)) {
                s->places[s->count]=i*player->row_cnt+j; 
                s->count++;
            }
        }
    }
}

// 获取位置权重值
int get_position_weight(struct Player *player, int x, int y) {
    if(player->row_cnt==8) {
        return pos8_weights[x][y];
    }
    else if(player->row_cnt==10) {
        return pos10_weights[x][y];
    }
    else {
        return pos12_weights[x][y];
    }
}

// 合并参数状态的计算，减少棋盘遍历次数（之前遍历三次） 10*10
void get_board_status_10(char** board, struct Player *player, 
                        int *mobility, int *stability, int *count_diff, int* empty_count) {
    int my_mob = 0, op_mob = 0;
    int my_stab = 0, op_stab = 0;
    int my_count = 0, op_count = 0;
    
    for(int i=0; i<player->row_cnt; i++) {
        for(int j=0; j<player->col_cnt; j++) {
            // 计算机动性以及判断开局中局残局
            if(board[i][j] != OP && board[i][j] != ME) {
                *empty_count++;
                if(is_valid_place(board, player, i, j)) my_mob++;
                if(is_valid_place_opponent(board, player, i, j)) op_mob++;
            }
            // 计算稳定性
            else if(board[i][j] == ME) {
                my_stab += get_position_weight(player, i, j);
                my_count++;
            }
            else if(board[i][j] == OP) {
                op_stab += get_position_weight(player, i, j);
                op_count++;
            }
        }
    }
    
    *mobility = my_mob - op_mob;
    *stability = my_stab - op_stab;
    *count_diff = my_count - op_count;
}

// 合并参数状态的计算，减少棋盘遍历次数（之前遍历三次） 12*12
void get_board_status_12(char** board, struct Player *player, 
                        int *stability, int *count_diff, int* empty_count) {
    int my_stab = 0, op_stab = 0;
    int my_count = 0, op_count = 0;
    
    for(int i=0; i<player->row_cnt; i++) {
        for(int j=0; j<player->col_cnt; j++) {
            // 计算机动性以及判断开局中局残局
            if(board[i][j] != OP && board[i][j] != ME) {
                *empty_count++;
            }
            // 计算稳定性
            else if(board[i][j] == ME) {
                my_stab += get_position_weight(player, i, j);
                my_count++;
            }
            else if(board[i][j] == OP) {
                op_stab += get_position_weight(player, i, j);
                op_count++;
            }
        }
    }

    *stability = my_stab - op_stab;
    *count_diff = my_count - op_count;
}

// 棋盘评估函数 10*10
int evaluate_board_10(char** board, struct Player *player) {
    // 计算棋盘空格数量
    int total = player->row_cnt * player->col_cnt;
    int empty_count = 0;
    // 一次遍历计算所有状态和参数
    int mobility_score=0, stability_score=0, count_difference=0;
    get_board_status_10(board, player, &mobility_score, &stability_score, &count_difference, &empty_count);
    // 定义阶段阈值（起手、开局、中局、残局）
    int early_threshold = total * 0.9; // 起手：空格大于棋盘格子的0.8
    int early_mid_threshold = total * 0.6; // 开局：空格介于4/5到1/2之间
    int mid_threshold = total * 0.25;     // 中局：空格介于1/2到1/4之间  // 残局：空格小于1/4

    // 根据空格数量确定当前阶段
    double mobility_weight, stability_weight, count_weight;
    if (empty_count > early_threshold) {
        // 起手阶段：
        mobility_weight =10* 1.0;
        stability_weight = 0;
        count_weight = 0;
    } else if (empty_count > early_mid_threshold) {
        // 开局阶段：
        mobility_weight =10* 0.5;
        stability_weight = 0.5;
        count_weight = 0.3;
    } else if (empty_count > mid_threshold) {
        // 中局阶段：注重稳定性
        mobility_weight =10* 0.3;
        stability_weight = 0.8;
        count_weight = 0.5;
    }else {
        // 残局:
        mobility_weight =10* 0;
        stability_weight = 0.3;
        count_weight = 1.2;
    }

    // 加权求和
    int score = (int)(
        mobility_weight * mobility_score +
        stability_weight * stability_score +
        count_weight * count_difference
    );

    return score;
}

// 棋盘评估函数 12*12
int evaluate_board_12(char** board, struct Player *player) {
    // 计算棋盘空格数量
    int total = player->row_cnt * player->col_cnt;
    int empty_count = 0;
    // 一次遍历计算所有状态和参数
    int stability_score=0, count_difference=0;
    get_board_status_12(board, player, &stability_score, &count_difference, &empty_count);
    // 定义阶段阈值（开局、中局、残局）
    int early_threshold = total * 0.8; // 起手：空格大于棋盘格子的0.8
    int early_mid_threshold = total * 0.5; // 开局：空格介于9/10到1/2之间
    int mid_threshold = total * 0.25;     // 中局：空格介于1/2到1/4之间  // 残局：空格小于1/4

    // 根据空格数量确定当前阶段
    double stability_weight, count_weight;
    if (empty_count > early_threshold) {
        // 起手阶段
        stability_weight = 0.1* 1.0;
        count_weight = 0.5;
    } else if (empty_count > early_mid_threshold) {
        // 开局阶段
        stability_weight = 0.1* 0.6;
        count_weight = 0.5;
    } else if (empty_count > mid_threshold) {
        // 中局阶段：
        stability_weight = 0.1* 1.5;
        count_weight = 1.0;
    }else {
        // 残局: 
        stability_weight = 0.1* 0.5;
        count_weight = 1.8;
    }

    // 加权求和
    int score = (int)(
        stability_weight * stability_score  +
        count_weight * count_difference
    );

    return score;
}

// Alpha-Beta剪枝搜索 10*10
int alphabeta_10(char** board, struct Player *player, int depth, int alpha, int beta, bool is_maximizing) {
    if (depth == 0) {
        return evaluate_board_10(board, player);
    }
    
    strategy s;
    if (is_maximizing) {
        init_strategy(board, player, &s);
        if (s.count == 0) {
            return alphabeta_10(board, player, depth-1, alpha, beta, false);
        }

        int max_eval = -999999;
        for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;

            char** new_board = cpy_board(player, board);
            make_place(new_board, player, x, y);

            int eval = alphabeta_10(new_board, player, depth-1, alpha, beta, false);
            free_board(player, new_board);

            max_eval = (eval > max_eval) ? eval : max_eval;
            alpha = (alpha > eval) ? alpha : eval;
            
            if (beta <= alpha) {
                    break;
                }
        }
        return max_eval;
    } else {
        init_strategy_opponent(board, player, &s);
        
        if (s.count == 0) {
            return alphabeta_10(board, player, depth-1, alpha, beta, true);
        }
        
        int min_eval = 999999;
        for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;
            
            char** new_board = cpy_board(player, board);
            make_place_opponent(new_board, player, x, y);

            int eval = alphabeta_10(new_board, player, depth-1, alpha, beta, true);
            free_board(player, new_board);

            min_eval = (eval < min_eval) ? eval : min_eval;
            beta = (beta < eval) ? beta : eval;
            
            if (beta <= alpha) {
                    break;
                }
        }
        return min_eval;
    }
}

// 12*12 的ab搜索
int alphabeta_12(char** board, struct Player *player, int depth, int alpha, int beta, bool is_maximizing) {
    if (depth == 0) {
        return evaluate_board_12(board, player);
    }
    
    strategy s;
    if (is_maximizing) {
        init_strategy(board, player, &s);
        if (s.count == 0) {
            return alphabeta_12(board, player, depth-1, alpha, beta, false);
        }

        int max_eval = -999999;
        for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;

            char** new_board = cpy_board(player, board);
            make_place(new_board, player, x, y);

            int eval = alphabeta_12(new_board, player, depth-1, alpha, beta, false);
            free_board(player, new_board);

            max_eval = (eval > max_eval) ? eval : max_eval;
            alpha = (alpha > eval) ? alpha : eval;
            
            if (beta <= alpha) {
                    break;
                }
        }
        return max_eval;
    } else {
        init_strategy_opponent(board, player, &s);
        
        if (s.count == 0) {
            return alphabeta_12(board, player, depth-1, alpha, beta, true);
        }
        
        int min_eval = 999999;
        for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;
            
            char** new_board = cpy_board(player, board);
            make_place_opponent(new_board, player, x, y);

            int eval = alphabeta_12(new_board, player, depth-1, alpha, beta, true);
            free_board(player, new_board);

            min_eval = (eval < min_eval) ? eval : min_eval;
            beta = (beta < eval) ? beta : eval;
            
            if (beta <= alpha) {
                    break;
                }
        }
        return min_eval;
    }
}

int get_dynamic_search_depth_10(char** board, struct Player *player)
{
    int TOTAL_CELLS = player->row_cnt * player->col_cnt;

    int empty_count_10=0;
    for(int i=0; i<player->row_cnt; i++) {
        for(int j=0; j<player->col_cnt; j++) {
            if(board[i][j] != OP && board[i][j] != ME) {
                empty_count_10++;
            }
        }
    }
    
    // 定义不同阶段的搜索深度
    if (empty_count_10 > TOTAL_CELLS * 0.8) {
        // 开局阶段 ：浅搜索
        return 3;
    } else if (empty_count_10 > TOTAL_CELLS * 0.3) {
        // 中局阶段 ：中等搜索
        return 3;
    } else if (empty_count_10 > TOTAL_CELLS * 0.15) {
        // 中残局阶段 ：较深搜索
        return 4;
    } else if (empty_count_10 > 12) {
        // 残局阶段 ：深搜索
        return 5;
    } else {
        // 终局阶段：最大搜索深度
        return 6;
    }
}

int get_dynamic_search_depth_12(char** board, struct Player *player)
{
    int TOTAL_CELLS = player->row_cnt * player->col_cnt;

    int empty_count_12=0;
    for(int i=0; i<player->row_cnt; i++) {
        for(int j=0; j<player->col_cnt; j++) {
            if(board[i][j] != OP && board[i][j] != ME) {
                empty_count_12++;
            }
        }
    }
    
    // 定义不同阶段的搜索深度
    if (empty_count_12 > TOTAL_CELLS * 0.9) {
        // 开局阶段 ：浅搜索
        return 3;
    } else if (empty_count_12 > TOTAL_CELLS * 0.5) {
        // 中局阶段 ：中等搜索
        return 3;
    } else if (empty_count_12 > TOTAL_CELLS * 0.25) {
        // 中残局阶段 ：较深搜索
        return 4;
    } else if (empty_count_12 > 12) {
        // 残局阶段 ：深搜索
        return 4;
    } else {
        // 终局阶段：最大搜索深度
        return 5;
    }
}

// 选择落子位置的主函数
struct Point place(struct Player *player) {
    // 8x8棋盘使用专用算法（位运算优化）
    if (player->row_cnt == 8 && player->col_cnt == 8) {
        uint64_t me = 0, op = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                int idx = pos_to_idx_8(x, y);
                if (player->mat[x][y] == 'O') {
                    me |= 1ULL << idx;
                } else if (player->mat[x][y] == 'o') {
                    op |= 1ULL << idx;
                }
            }
        }

        Strategy_8 my_moves;
        init_strategy_me_8(me, op, &my_moves);
        if (my_moves.count == 0) {
            return initPoint(-1, -1);
        }

        int best_idx = 0;
        int best_val = -1000000;
        for (int i = 0; i < my_moves.count; i++) {
            uint64_t new_me, new_op;
            make_place_me_8(me, op, my_moves.positions[i], &new_me, &new_op);

            int max_search_depth_8 = get_dynamic_search_depth_8(new_me,new_op);//使用动态深度发挥算力优势

            int val = alphabeta_8(new_me, new_op, max_search_depth_8 - 1, -1000000, 1000000, false);
            if (val > best_val) {
                best_val = val;
                best_idx = i;
            }
        }

        int best_pos = my_moves.positions[best_idx];
        return initPoint(idx_to_x_8(best_pos), idx_to_y_8(best_pos));
    } 
    // 其他尺寸使用常规算法
    else if (player->row_cnt == 10){
        // 10*10
        char** board = cpy_board(player, player->mat);
        strategy s;
        init_strategy(board, player, &s);
        
        if(s.count == 0) {
            free_board(player, board);
            return initPoint(-1, -1);
        }
        
        int best_value = -999999;
        int best_move = 0;
        
        if(player->row_cnt == 10)
        {
            for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;
            
            char** new_board = cpy_board(player, board);
            make_place(new_board, player, x, y);
            
            int max_search_depth_10 = get_dynamic_search_depth_10(new_board,player);

            int value = alphabeta_10(new_board, player, max_search_depth_10 - 1, -999999, 999999, false);
            free_board(player, new_board);
            
            if(value > best_value) {
                best_value = value;
                best_move = i;
            }
            }
        }else{
            for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;
            
            char** new_board = cpy_board(player, board);
            make_place(new_board, player, x, y);
            
            int max_search_depth_10 = get_dynamic_search_depth_10(new_board,player);

            int value = alphabeta_10(new_board, player, max_search_depth_10 - 1, -999999, 999999, false);
            free_board(player, new_board);
            
            if(value > best_value) {
                best_value = value;
                best_move = i;
            }
            }
        }
        int best_x = s.places[best_move] / player->row_cnt;
        int best_y = s.places[best_move] % player->row_cnt;
        
        free_board(player, board);
        return initPoint(best_x, best_y);
    }else{
        // 12*12
        char** board = cpy_board(player, player->mat);
        strategy s;
        init_strategy(board, player, &s);
        
        if(s.count == 0) {
            free_board(player, board);
            return initPoint(-1, -1);
        }
        
        int best_value = -999999;
        int best_move = 0;
        
        if(player->row_cnt == 10)
        {
            for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;
            
            char** new_board = cpy_board(player, board);
            make_place(new_board, player, x, y);
            
            int max_search_depth_12 = get_dynamic_search_depth_12(new_board,player);

            int value = alphabeta_12(new_board, player, max_search_depth_12 - 1, -999999, 999999, false);
            free_board(player, new_board);
            
            if(value > best_value) {
                best_value = value;
                best_move = i;
            }
            }
        }else{
            for(int i=0; i<s.count; i++) {
            int x = s.places[i] / player->row_cnt;
            int y = s.places[i] % player->row_cnt;
            
            char** new_board = cpy_board(player, board);
            make_place(new_board, player, x, y);
            
            int max_search_depth_12 = get_dynamic_search_depth_12(new_board,player);

            int value = alphabeta_12(new_board, player,max_search_depth_12 - 1, -999999, 999999, false);
            free_board(player, new_board);
            
            if(value > best_value) {
                best_value = value;
                best_move = i;
            }
            }
        }
        int best_x = s.places[best_move] / player->row_cnt;
        int best_y = s.places[best_move] % player->row_cnt;
        
        free_board(player, board);
        return initPoint(best_x, best_y);
    }
}

// 初始化函数（空实现）
void init(struct Player *player) {
    return;
}


/* ==============================
 *           FINAL BOSS          
 *        💩 THE HOLY SHIT 💩    
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *  
 *   __________________________  
 *  |                          | 
 *  |     (  )_(  )            | 
 *  |    (   •  •   )          | 
 *  |   (     🚽     )         | 
 *  |    (   ___   )           | 
 *  |      |_____|             | 
 *  |__________________________| 
 * ==============================
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */