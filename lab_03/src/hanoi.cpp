#include <iostream>
#include "List.cpp"

void move (int disk_amount, int from, int to, int temp, List<int> &list) {
    if (disk_amount == 0)
        return;
    move(disk_amount - 1, from, temp, to, list);

    list.add_node(from);
    list.add_node(to);
    move(disk_amount - 1, temp, to, from, list);
}

void print_info(List<int> list) {
    auto cur = list.get_root();
    while(cur != nullptr) {
        int from = cur->get_value();
        cur = cur->get_next();
        int to = cur->get_value();
        std::cout << "From " << from << " to " << to << std::endl << std::flush;
        cur = cur->get_next();
    }
}

int main() {
    int DISKS_COUNT = 8;
    List<int> list;
    move(DISKS_COUNT, 1,2,3, list);
    print_info(list);
    list.DeleteLinkedList();
    return 0;
}
