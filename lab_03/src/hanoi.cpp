#include <iostream>
#include "List.cpp"
#include <vector>

void move (int disk_amount, int from, int to, int temp, List<std::vector<int> > &list) {
    if (disk_amount == 0)
        return;
    move(disk_amount - 1, from, temp, to, list);
    std::vector<int> tmp {from, to};
    list.add_node(tmp);
    move(disk_amount - 1, temp, to, from, list);
}

void print_info(List<std::vector<int> > list) {
    auto cur = list.get_root();
    while(cur != nullptr) {
        auto values = cur->get_value();
        int from = values[0];
        int to = values[1];
        std::cout << "From " << from << " to " << to << std::endl << std::flush;
        cur = cur->get_next();
    }
}

int main() {
    int DISKS_COUNT = 8;
    List<std::vector<int> > list;
    move(DISKS_COUNT, 1,2,3, list);
    print_info(list);
    list.DeleteLinkedList();
    return 0;
}
