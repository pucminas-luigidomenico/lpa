#include <iostream>
#include <vector>

int main() {
    // freopen("input.in", "r", stdin);
    
    // Dia final
    int n;
    std::cin >> n;
    
    while (n != 0) {
        // Vetor contendo a quantidade de bactérias criadas
        // nos dias inicias
        std::vector<int> bacteries(4);
        
        // Bactérias criadas nos dias iniciais (4 primeiros dias)
        std::cin >> bacteries[0] >> bacteries[1] 
                    >> bacteries[2] >> bacteries[3];
        
        // Total de bactérias nos 4 primeiros dias
        int total = bacteries[0] + bacteries[1]
                    + bacteries[2] + bacteries[3];
        
        // A partir do quinto dia, o total dobra,
        // devido a reprodução das bactérias
        for (int i = 4; i < n; i++) {
            total *= 2;
            
            // Mas, as bactérias de 4 dias atrás morrem
            total -= bacteries[i - 4];
        }
        
        // Total de bactérias no último dia
        std::cout << total % 13371337 << std::endl;
        
        // Próximo caso de teste
        std::cin >> n;
    }
    return 0;
}