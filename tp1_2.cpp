#include <iostream>
#include <ctime>


using namespace std;

void printImagem(int ** imagem, int c, int l)
{
	//imprime a imagem de saida
	cout << "P1"<<endl;
	cout << c<< " " <<l<<endl;
	for(int y = 0 ; y < l; y++)
	{
		for(int x = 0 ; x < c; x++)
			 cout<< imagem[y][x]<< " ";
		cout <<endl;
	}
	cout <<endl;
}

int numQuadradosPintados(int **saida, int c, int l, int py, int px)
{
	/*Função que conta quantos quadrados estão estão na posição analisada e os vizinhos*/
	int quadrados = 0;
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] == 1)//se o quadrado estiver pintado
						quadrados++;//adiciona ele ao contador


	return quadrados;//retorna numero de quadrados pintados
}

int numQuadradosSemX(int **saida, int c, int l, int py, int px)
{
	/*Função que conta quantos quadrados sem X estão na posição analisada e os vizinhos*/
	int quadrados = 0;
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 0) //se o quadrado não estiver com X (=0))
						quadrados++;//adiciona ele ao contador

	return quadrados;//retorna numero de quadrados sem X
}

void preenchePreto(int **saida, int c,int l, int py, int px)
{
	/*Função que preenche os quadrados da posição recebida e dos vizinhos*/
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 0) // se não estiver com X, podemos preencher
						saida[py+i][px+j] = 1;//preenche o quadrado de preto
}


void preencheX(int **saida, int c,int l, int py, int px)
{
	/*Função que marca X os quadrados da posição recebida e dos vizinhos*/
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 1) // se não estiver já preenchido, marca X
						saida[py+i][px+j] = 0; // marca X no quadrado
}

void fill_a_pix(int **entrada, int **saida, int c, int l)
{
	//Resolução que utiliza técnicas para se resolver o fill a pix
	//Primeira Passada
	/*
		Preenche as dicas básicas
		0 = quadrado com X
		1 = quadrado preenchido
		-1 = quadrado vazio
	*/
	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)	
		{
			if(entrada[y][x] == 0)//se for zero, todos ao redor devem ser marcados com X
				preencheX(saida,c,l,y,x);
			if(entrada[y][x] > 0)
				if(entrada[y][x] == numQuadradosSemX(saida,c,l,y,x))
				//se o numero dos quadrados da posição e do entorno for igual ao número da posição
					preenchePreto(saida,c,l,y,x);//preenche tudo de preto
		}

	bool preencher = true;

	//Nesse ponto todas as dicas básicas para se resolver o fill-a-pix foram preenchidas
	//resta agora utilizar as dicas básicas para solucionar o problema

	while(preencher)
	{
		preencher = false;
		for(int y = 0; y < l; y++)
			for(int x = 0; x < c; x++)	
			{
				if(saida[y][x] == -1)//enquanto houver quadrados que não foram marcados com X nem foram preenchidos
					preencher = true;//continua a procurar as pistas

				if(entrada[y][x] > 0)
				{
					if(entrada[y][x] == numQuadradosSemX(saida,c,l,y,x))//se o numero de quadrados da posição e no entorno sem x for igual aos quadrados disponíveis
						preenchePreto(saida,c,l,y,x);//podemos preencher tudo de preto

					if(numQuadradosPintados(saida,c,l,y,x) == entrada[y][x])//se já preenchemos essa posição e o entorno 
						preencheX(saida,c,l,y,x);//preenche o resto com X
				}
			}
	}
	return;
}

int main()
{
	int c,l;
	cin >> c >> l; //m = nº de colunas e n = nº de linhass

	int **entrada = new int *[l]; //matriz que recebe o jogo
	int **saida = new int *[l]; //matriz que recebe a imagem final

	//aloca-se mais duas linhas e duas colunas para preencher de zeros as bordas
	//isso facilita a comparação dos quadrados
	for(int i = 0; i < l; i++)
	{
		entrada[i] = new int[c];
		saida[i] = new int[c];

	}

	//preenchendo as matrizes com -1, inclusive as bordas
	for(int i = 0; i < l ; i++)
		for(int j = 0; j < c ; j++)
			saida[i][j] = -1;

	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
		{
			cin >> entrada[y][x];
		}

	
	/*A função fill-a-pix resolverá o problema utilizando as "dicas básicas"
	que o problema dá:
	.Se a posição analisada tem número 0 : todos os quadrados em torno, inclusive
	o que tem o 0 devem ser marcados com X( X = 0)
	.Se a posição analisada tem o número 9 : todos os quadrados em torno, inclusive
	o que tem o 9 podem ser preenchidos (quadrado preenchido = 1)
	Qualquer posição que possua um número e que o número de quadrados em seu entorno
	junto com ela mesma for igual ao número que ela , podemos preencher todas as posições
	inclusive a que guarda o número
	.Se uma posição que guarda um número e todos o número de quadrados preenchidos em seu entorno
	já for igual a esse número, podemos preencher o restante com X
	.Quando uma posição guarda um número e o número de quadrados que não estiverem
	com X for igual ao número que ela guarda, podemos preencher todos os quadrados sem X*/
	clock_t t0 = clock();
	fill_a_pix(entrada,saida,c,l);
	cerr << "Tempo de resolução do problema (ms): " << ((clock()-t0)*1.0/CLOCKS_PER_SEC)*1000 << endl;
	printImagem(saida,c,l);
	

	for(int i = 0; i < l; i++)
	{
		delete [] entrada[c];
		delete [] saida[c];
	}

	delete [] entrada;
	delete [] saida;
	cerr << "Tempo total de execução (ms): " << ((clock()-t0)*1.0/CLOCKS_PER_SEC)*1000 << endl;

	return 0;
}