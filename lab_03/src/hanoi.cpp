#include <iostream>
#include "List.cpp"

void move (int disk_amount, int from, int to, int temp, List<int *> list) {
    if (disk_amount == 0)
        return;
    move(disk_amount - 1, from, temp, to, list);
    std::cout << "From " << from << " to " << to << std::endl;
    int to_add[] = {from, to};
    list.add_node(to_add);
    move(disk_amount - 1, temp, to, from, list);
}

void print_info(List<int *> list) {
    auto cur = list.get_root();
    while(cur != nullptr) {
        auto values = cur->get_value();
        int from = values[0], to = values[1];
        std::cout << "From " << from << " to " << to << std::endl;
        cur = cur->get_next();
    }
}

int main() {
    int DISKS_COUNT = 8;
    List<int *> list;
    move(DISKS_COUNT, 1,2,3, list);
    print_info(list);
    list.DeleteLinkedList();
    return 0;
}
