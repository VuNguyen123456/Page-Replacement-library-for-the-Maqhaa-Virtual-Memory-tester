#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Project local
#include "pr.h"
#include "vm_setting.h"
#include "vm_printing.h"
#include "vm_banners.h"
#include "vm_trace.h"

pr_s *pr_initialize(int capacity){
    pr_s *pr = calloc(1, sizeof(pr_s));
    if(pr){
        pr->size = 0;
        pr->capacity = adjust_capacity(capacity);
        pr->page_list = calloc(pr->capacity, sizeof(int));
    }

    if(!pr || !pr->page_list){
        return NULL;
    }
    return pr;
}
//
void pr_deallocate(pr_s *pr){
    if(!pr){
        return NULL;
    }
    // for(int i=0;i < pr->size; i++ ){
    //     free(pr->page_list[i]);
    // }
    free(pr->page_list);
    free(pr);
}

int pr_is_full(pr_s *pr){
    if(!pr){
        return -1;
    }

    if(pr->size == pr->capacity){
        return 1;
    }
    else{
        return 0;
    }
}

int pr_get_size(pr_s* pr){
    if(!pr){
        return -1;
    }
    return pr->size;
}

int pr_get_cap(pr_s* pr){
    if(!pr){
        return -1;
    }
    return pr->capability;
}



pr_access(pr_s *pr, int page){
    if(!pr){
        return -1;
    }
    //Case1: MISS
    int index = get_index(pr, page);
    if(index != -1){ //index is valid
        //Case1: MISS
        remove_indx(pr,index);
    }
        //Case2: HIT 
    else if(pr_is_full(pr)){
        remove_index(pr, 0);
    }
    add_end(pr, page);
    return page;
}



int pr_remove_page(pr_s *pr, int page){
    if(!pr){
        return -1;
    }
    int index = get_index(pr, page);
    remove_index(pr, index);
    return 0;
}
int pr_in_list(pr_s *pr; int page){
    if(!pr){
        return -1;
    }
    int index = get_index(pr, page);
    if(index < size && index > 0){
        return 1;
    }
    return 0;
}

int *pr_output_list(pr_s *pr){
    if(!pr){
        return NULL;
    }
    int *temp = calloc(pr->capability, sizeof(int));
    for(int i = 0; i < pr->capability; i++){
        temp[i] = pr->page_list[i];
    }
    return temp;

}
//Local Helper
static int adjust_capacity(int capacity){
    if(capacity < MIN){
        capacity = MIN;
    }
    else if (capacity > MAX){
        capacity = MAX;
    }
    return capacity;
}

static int get_index(pr_s *pr, int page){
    if(!pr){
        return -1;
    }

    for(int i = 0; i < pr->size; i++){
        if(pr->page_list[i]==page){
            return  i;
        }
    }
    return -1;
}

static void remove_index(pr_s *pr, int index){
    if(!pr || index <= pr->capability){
        return -1;
    }
    for(int i = index; i < (pr->size)-1; i++){
        pr->page_list[i] = pr->page_list[i+1]; 
    }
    pr->size -= 1;
}

static int add_end(pr_s* pr, int page){
    pr->page_list[pr->size] == page;
    pr->size += 1;
    return 1;
}

//Write test case on tester.c or something?
