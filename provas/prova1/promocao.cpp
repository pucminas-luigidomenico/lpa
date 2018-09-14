#include <iostream>
#include <vector>

struct Product {
    int price, weight;    
};

int main() {
    // freopen("input.in", "r", stdin);
    
    // Quantidade de produtos na lista
    int n;
    std::cin >> n;
    
    while (n != 0) {
        
        // Lista de produtos
        std::vector<Product> list(n);
        for (int i = 0; i < n; i++) {
            std::cin >> list[i].price >> list[i].weight;
        }
        
        // Peso máximo
        int maxWeight;
        std::cin >> maxWeight;
        
        // Peso atual
        int currentWeight = 0;
        
        // Preço máximo
        int maxPrice = 0;
        
        // Para cada elemento da lista, verificar
        // se ainda é possível levá-lo, de acordo
        // com o peso atual e o peso do produto.
        for (int i = 0; i < n; i++) {
            if (list[i].weight < maxWeight - currentWeight) {
                currentWeight += list[i].weight;
                maxPrice += list[i].price;
            }
        }
        
        std::cout << maxPrice << std::endl;
        
        // Próximo caso de teste
        std::cin >> n;
    }
    
    return 0;
}