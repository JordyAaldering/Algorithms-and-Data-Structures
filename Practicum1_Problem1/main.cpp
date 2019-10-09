#include <iostream>

int main()
{
    int num_pis, num_cons;
    std::cin >> num_pis >> num_cons;

    int cons[num_cons][2];
    for (auto& con : cons) {
        std::cin >> con[0] >> con[1];
    }

    return 0;
}
