#ifndef BEST_WIN_LOSS_RATIO_H_
#define BEST_WIN_LOSS_RATIO_H_

struct BestWinLossRatio
{
    //variables to track best win loss ratio move
    double best_win_loss_ratio = 0;

    int best_win_loss_ratio_node_id = -1;

    unsigned int time_shuffle_and_fill_up_board = 0;
    unsigned int time_who_won_using_dfs_algo = 0;
};

#endif // !BEST_WIN_LOSS_RATIO_H_