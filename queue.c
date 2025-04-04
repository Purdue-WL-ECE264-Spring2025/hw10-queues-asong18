#include "queue.h"
#include "tile_game.h"

int VisitedBefore (struct linked_list*, uint64_t);

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
    struct linked_list VisitedNodes;
    VisitedNodes.head=NULL;
    insert_at_head(&VisitedNodes, serialize(start));
    while (q.data.head != NULL) {
        struct game_state cur = dequeue (&q);
        if (cur.tiles[0][0] == 1 && cur.tiles[0][1] == 2 && cur.tiles[0][2] == 3 && cur.tiles[0][3] == 4 &&
            cur.tiles[1][0] == 5 && cur.tiles[1][1] == 6 && cur.tiles[1][2] == 7 && cur.tiles[1][3] == 8 &&
            cur.tiles[2][0] == 9 && cur.tiles[2][1] == 10 && cur.tiles[2][2] == 11 && cur.tiles[2][3] == 12 &&
            cur.tiles[3][0] == 13 && cur.tiles[3][1] == 14 && cur.tiles[3][2] == 15 && cur.tiles[3][3] == 0){
            free_list (VisitedNodes);
            free_list (q.data);
            return cur.num_steps;
        } else {
            struct game_state child = cur;
            move_up(&child);
            if (child.empty_row != cur.empty_row){
                uint64_t val = serialize(child);
                if (!VisitedBefore(&VisitedNodes, val)) {
                    child.num_steps = cur.num_steps + 1;
                    enqueue(&q, child);
                    insert_at_head(&VisitedNodes, val); 
                }
            }
            child = cur;
            move_down(&child);
            if (child.empty_row != cur.empty_row){
                uint64_t val = serialize(child);
                if (!VisitedBefore(&VisitedNodes, val)) {
                    child.num_steps = cur.num_steps + 1;
                    enqueue(&q, child);
                    insert_at_head(&VisitedNodes, val); 
                }
            }
            child = cur;
            move_left(&child);
            if (child.empty_col != cur.empty_col) {
                uint64_t val = serialize(child);
                if (!VisitedBefore(&VisitedNodes, val)) {
                    child.num_steps = cur.num_steps + 1;
                    enqueue(&q, child);
                    insert_at_head(&VisitedNodes, val); 
                }
            }
            child = cur;
            move_right(&child);
            if (child.empty_col != cur.empty_col) {
                uint64_t val = serialize(child);
                if (!VisitedBefore(&VisitedNodes, val)) {
                    child.num_steps = cur.num_steps + 1;
                    enqueue(&q, child);
                    insert_at_head(&VisitedNodes, val); 
                }
            }
        }
    }
    return 0;
}
int VisitedBefore (struct linked_list * list, uint64_t val){
    struct list_node *current = list->head;
    while (current != NULL){
        if (current->value == val){
            return 1;
        }
        current = current->next;
    }
    return 0;
}
