#include <iostream>

int main() {
    // freopen("input.in", "r", stdin);
    
    // Os 3 amigos aprensentam uma única ordenação
    // Assim, se na fila tiver 4 pessoas, a única
    // pessoa que pode aparecer de formas distintas
    // é a que não faz parte do grupo (4 possibildades).
    // Seja n o número de pessoas na fila:
    int n;
    std::cin >> n;
    
    while (n != 0) {
        // Total de possibildades é inicialmente 1,
        // pois com apenas os 3 amigos na fila existe
        // uma única possibildade.
        int total = 1;
        for (int i = n; i > 3; i--) {
            total *= i;
        }
        
        std::cout << total << std::endl;
        
        // Próximo caso de teste
        std::cin >> n;
    }
    
    return 0;
}