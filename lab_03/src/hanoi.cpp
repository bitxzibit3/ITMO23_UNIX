#include <iostream>
#include "List.cpp"

void move (int disk_amount, int from, int to, int temp, List<std::pair<int, int> > &list) {
    if (disk_amount == 0)
        return;
    move(disk_amount - 1, from, temp, to, list);
    std::pair<int, int> tmp (from, to);
    list.add_node(tmp);
    move(disk_amount - 1, temp, to, from, list);
}

void print_info(List<std::pair<int, int> > list) {
    auto cur = list.get_root();
    int iter_counter = 0;
    while(cur != nullptr) {
        auto values = cur->get_value();
        int from = values.first;
        int to = values.second;
        std::cout << "From " << from << " to " << to << std::endl;
        cur = cur->get_next();
        iter_counter++;
    }
    std::cout << "Iterations count: " << iter_counter << std::endl;
}

int main() {
    int DISKS_COUNT = 8;
    List<std::pair<int, int> > list;
    move(DISKS_COUNT, 1,2,3, list);
    print_info(list);
    list.DeleteLinkedList();
    return 0;
}
