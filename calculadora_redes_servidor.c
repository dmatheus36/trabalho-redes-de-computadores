#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <math.h>

int Calc(char *);
char * verificarSinalOuTermino(char *);
char * itoa(int, char *);

int main(int argc, char const* argv[])
{

	
	int servSockD = socket(AF_INET, SOCK_STREAM, 0);

	
	char sendMsg[255];
	char rcvMsg[255];
	int resultado;

	
	struct sockaddr_in servAddr;

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9001);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	
	bind(servSockD, (struct sockaddr*)&servAddr,
		sizeof(servAddr));

	
	listen(servSockD, 1);

	
	int clientSocket = accept(servSockD, NULL, NULL);

	recv(clientSocket, rcvMsg, sizeof(rcvMsg), 0);

	resultado = Calc(rcvMsg);
	itoa(resultado, sendMsg);

	
	send(clientSocket, sendMsg, sizeof(sendMsg), 0);

	return 0;
}

int Calc(char *argv) {
    char * aux = argv;
    int soma = 0;
    char operacaoMatematica;
    soma += atoi(aux);
    for(; *aux != '\0';) {
        
        aux = verificarSinalOuTermino(aux);

        operacaoMatematica = aux[0];

        switch (operacaoMatematica)
        {
        case '+':
            aux++;
            soma += atoi(aux);
            break;
        case '-':
            aux++;
            soma -= atoi(aux);
            break;
        case '*':
            aux++;
            soma *= atoi(aux);
            break;
        case '/':
            aux++;
            soma /= atoi(aux);
            break;
        
        default:
            break;
        }
    }

    return soma;

}

char * verificarSinalOuTermino(char *aux) {
    while((*aux != '+') && (*aux != '-') && (*aux != '*') && (*aux != '/') && (*aux != '\0')) {
            aux++;
        }

        return aux;
}

char *itoa (int num, char*buffer) {
    int current = 0;
    int base = 10;
    if (num == 0) {
        buffer[current++] = '0';
        buffer[current] = '\0';
        return buffer;
    }

    int num_digits = 0;

    if (num < 0) {
        if (base == 10) {
            num_digits++;
            buffer[current] = '-';
            current++;
            num *= -1;
        } else {
            NULL;
        }
    }

    num_digits += (int) floor(log(num)/log(base)) +1;

    while (current < num_digits) {
        int base_val = (int) pow(base, num_digits-1-current);
        int num_val = num / base_val;
        char value = num_val+'0';
        buffer[current] = value;
        current++;
        num -= base_val * num_val;
    }

    buffer[current] = '\0';
    return buffer;
}
