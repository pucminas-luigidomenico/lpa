#include <iostream>
#include <vector>

struct Ball {
    int x, y;          
};

int calcDistance(const Ball &b1, const Ball &b2) {
    return (b1.x - b2.x) * (b1.x - b2.x) 
            + (b1.y - b2.y) * (b1.y - b2.y);
}

int main() {
    //freopen("input.in", "r", stdin);
    
    // Quantidade de casos de testes da entrada
    int c;
    std::cin >> c;
  
    for (int i = 0; i < c; i++) {
        // Quantidade de bolas disponíveis, além da branca
        int n;
        std::cin >> n;
        
        // Bola branca
        Ball whiteBall;
        
        // Vetor contendo as bolas presentes no jogo
        // excluindo-se a branca
        std::vector<Ball> otherBalls(n);
        
        // Posição da bola branca
        std::cin >> whiteBall.x >> whiteBall.y;
        
        // Posição das demais bolas
        for (int j = 0; j < n; j++) {
            std::cin >> otherBalls[j].x >> otherBalls[j].y;
        }
        
        // Inicializa menor distância, calculando a distância
        // da bola branca em relação a distância da primeira
        // bola presente no vetor
        int minDistance = calcDistance(whiteBall, otherBalls[0]);
        int index = 1;
        
        // Percorre vetor para verificar se encontra distância menor
        for (int j = 1; j < n; j++) {
            int aux = calcDistance(whiteBall, otherBalls[j]);
            
            if (aux < minDistance) {
                minDistance = aux;
                index =  j + 1;
            }
        }
        
        std::cout << index << std::endl;
    }
    
    return 0;
}