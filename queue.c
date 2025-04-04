#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    uint64_t SerializedState = serialize (state);
    insert_at_tail(&q->data,SerializedState);
}

struct game_state dequeue(struct queue *q) { 
    uint64_t SerializedState = remove_from_head (&q->data);
    return deserialize(SerializedState);
}

int number_of_moves(struct game_state start) {
    struct queue q;
    q.data.head = NULL;
    enqueue (&q, start);
    while (q.data.head != NULL) {
        struct game_state cur = dequeue (&q);
        if (cur.tiles[0][0] == 1 && cur.tiles[0][1] == 2 && cur.tiles[0][2] == 3 && cur.tiles[0][3] == 4 &&
            cur.tiles[1][0] == 5 && cur.tiles[1][1] == 6 && cur.tiles[1][2] == 7 && cur.tiles[1][3] == 8 &&
            cur.tiles[2][0] == 9 && cur.tiles[2][1] == 10 && cur.tiles[2][2] == 11 && cur.tiles[2][3] == 12 &&
            cur.tiles[3][0] == 13 && cur.tiles[3][1] == 14 && cur.tiles[3][2] == 15 && cur.tiles[3][3] == 0){
            /*
            while (q.data.head != NULL) {
                dequeue(&q);
            }
            */
            return cur.num_steps;
        } else {
            struct game_state NextMove = cur;
            move_up(&NextMove);
            if (NextMove.empty_row < cur.empty_row){
                enqueue(&q, NextMove);
                NextMove.num_steps++;
            }
            NextMove = cur;
            move_down(&NextMove);
            if (NextMove.empty_row > cur.empty_row){
                enqueue(&q, NextMove);
                NextMove.num_steps++;
            }
            NextMove = cur;
            move_left(&NextMove);
            if (NextMove.empty_col < cur.empty_col) {
                enqueue(&q, NextMove);
                NextMove.num_steps++;
            }
            NextMove = cur;
            move_right(&NextMove);
            if (NextMove.empty_col > cur.empty_col) {
                enqueue(&q, NextMove);
                NextMove.num_steps ++;
            }
        }
    }
    return 0;
}
