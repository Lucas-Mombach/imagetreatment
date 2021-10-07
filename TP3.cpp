// INF110 - Trabalho pratico 3
//
// programa para ler, modificar e gravar uma imagem no formato PNM
//
// Autores: Andre Gustavo dos Santos			(criado em 16/06/14)
//          Andre Gustavo dos Santos			(modificado em 22/05/18)
//					Andre Gustavo dos Santos			(modificado em 13/09/21)

#include <iostream>
#include <fstream>
#include <cstring>


const int MAXALTURA  = 500;				//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;


using namespace std;

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA];	//a imagem propriamente dita
	int largura, altura;						//dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;						//arquivo que contem a imagem original
	ofstream arqsaida;							//arquivo que contera a imagem gerada
	char comentario[200], c;				//auxiliares
	int i, j, valor;								//auxiliares

	// Escolhe o arquivo desejado

	string arquivonpm;
	cout << "Nome do arquivo pnm: " <<endl;
	cin >> arquivonpm ;

	// 

//*** LEITURA DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Abertura do arquivo ***//
	arqentrada.open(arquivonpm,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo.pnm\n";
		return 0;
	}
	//***************************//


	//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();		//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
		cout << "Desculpe, ainda nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
													//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le o numero de pixels da horizontal e vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura>MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura>MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado)
	//****************************//


	//*** Leitura dos pixels da imagem ***//
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			arqentrada >> valor;
			imagem[i][j] = (unsigned char)valor;
		}
	//************************************//

	arqentrada.close();  //Fecha arquivo apos a leitura

//*** FIM DA LEITURA DA IMAGEM ***//



//*** TRATAMENTO DA IMAGEM ***//
//inicialmente e' nesta parte do codigo que voce vai trabalhar
	
	int fator;
	cout << "Qual o fator de escurecimento (1-100) ? ";
	cin >> fator;

	//*** Escurece a imagem ***//
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			valor = (int)imagem[i][j];			//pega o valor do pixel
			valor -= fator;									//escurece o pixel
			if (valor < 0)									//se der negativo
				valor = 0;										//  deixa preto
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
    //*************************//

	cout << "Qual o fator de clareamento (1-100) ? ";
	cin >> fator;

	//*** Clarea a imagem ***//
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			valor = (int)imagem[i][j];			//pega o valor do pixel
			valor += fator;									//escurece o pixel
			if (valor > 255)									//se der maior que 255
				valor = 255;										//  deixa branco
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
    //*************************//
		char resposta; // aplicar esse efeito?
		cout << "Deseja tornar a imagem negativa?(S/N)";
		cin >> resposta;
		//*** Negativar a imagem ***//
		if (resposta == 'S')
		{
			for ( i = 0; i < altura; i++)
			{
				for(j=0;j<largura;j++) {
				valor = (int)imagem[i][j];	//pega o valor do pixel

				if(valor < 127){						// pois 127+128/2 é a mediana de 255
				valor = 255-valor; 					// tera a mesma diferença que o valor tem de 0
			}
			if(valor > 127)
			{
				valor = 0+(255 - valor);
			}
			
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
		}
		}

		// 
	
//*** FIM DO TRATAMENTO DA IMAGEM ***//




//*** GRAVACAO DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Escolhe o nome para gravar a imagem ***//
	string novaImagem;
	cout << "Deseja salvar a imagem como:" ;
	cin >> novaImagem;
	//*** Grava a nova imagem ***//
	arqsaida.open(novaImagem,ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar " << novaImagem << endl;
		return 0;
	}

	arqsaida << tipo << endl;							//tipo
	arqsaida << "# INF110\n";							//comentario
	arqsaida << largura << " " << altura;	//dimensoes
	arqsaida << " " << 255 << endl;				//maior valor
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
			arqsaida << (int)imagem[i][j] << endl;	//pixels

	arqsaida.close();		//fecha o arquivo
	//***************************//

//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}
