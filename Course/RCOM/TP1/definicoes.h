#ifndef DEFINICOES_H
#define DEFINICOES_H

/***********************************************************************************************
	FUNCOES AUXILIARES AO TRATAMENTO DE DADOS
***********************************************************************************************/

void limparFrame(unsigned char frame[MTS])
{
	int i;
	for (i = 0; i < MTS; i++)
	{
		frame[i] = '\0';
	}
}

void limparPacote(unsigned char pkg[MFS + 10])
{
	int i;
	for (i = 0; i < (MFS + 10); i++)
	{
		pkg[i] = '\0';
	}
}

void limparDados(unsigned char pkg[MFS + 1])
{
	int i;
	for (i = 0; i < (MFS + 1); i++)
	{
		pkg[i] = '\0';
	}
}



/***********************************************************************************************
	FUNCOES TRATAMENTO DE DADOS
***********************************************************************************************/
int iFrameToPackage(unsigned char frame[MTS], int size, unsigned char pkg[MFS + 10]);
int iFrame(unsigned char pkg[MFS + 10], int size, unsigned char frame[MTS]);
void suFrameExtract(unsigned char frame[MTS]);
int suFrame(int emissor, int numSeq, int qualC, unsigned char frame[MTS]); // set, ua, disc, rr, rej

void packageToControl(unsigned char pkg[MFS + 10], int size, char * fileName, int * tamFile);
int controlToPackage( char * nomeFicheiro, int tamFicheiro, int modo, unsigned char pkg[MFS + 10]);
int dataToPackage(unsigned char data[MFS+1], int numSeq, int size, unsigned char pkg[MFS + 10]);
int packageToData(unsigned char pkg[MFS + 10], int size, unsigned char data[MFS + 1]);
/*======================================================
*		FUNCOES AO NIVEL DO LINK LAYER
=======================================================*/
int iFrameToPackage(unsigned char frame[MTS], int size, unsigned char pkg[MFS + 10])
{
	//printf("-------------------------\nFRAME I UNBUILDER\n-------------------------\n");
	
	//printf("Tamanho da trama: %d\n", size);
	//verDados(frame, size);
	
	limparPacote(pkg);
	
	unsigned char N = frame[0];
	unsigned char A = frame[1];
	unsigned char C = frame[2];
	unsigned char Bcc1 = (A ^ C);
	
	//printf("[0x%X, 0x%X, 0x%X, 0x%X, ..., 0x%X, 0x%X]\n", N, A, C, Bcc1, frame[size-1], frame[size]);
	
	if (Bcc1 != frame[3])
		printf("errou\n");
	
	//printf("Tamanho do trama I: %d\n", size);
	
	int limite = size - 2;
	int i;
	int j = 0;
	
	//printf("[FIRST, LAST] = [0x%X, 0x%X]\n", frame[4], frame[limite]);
	
	for (i = 4; i <= limite; i++)
	{
		if (frame[i] == ESC)
		{
			i++;
			if (frame[i] == 0x5e) // flag
			{
				pkg[j] = 0x7e;
				j++;
			}
			else if(frame[i] == 0x5d) // esc
			{
				pkg[j] = 0x7d;
				j++;
			}
		}
		else
		{
			pkg[j] = frame[i];
			j++;
		}
		
		//pkg[i - 4] = frame[i];
	}
	
	//verDados(pkg, (*tamPacote));
	
	return( j - 1 );
}

int iFrame(unsigned char pkg[MFS + 10], int size, unsigned char frame[MTS])
{
	limparFrame(frame);
	//printf("-------------------------\nFRAME I BUILDER\n-------------------------\n");
	//printf("Tamanho do pacote: %d\n", size);
	//verDados(pkg, size);
	
	int si = 0; //size of trama

	frame[0] = FLAG;
	frame[1] = 0x03;

	if(pkg[0] == 0x01) // pacote de dados
	{
		int num = (int) pkg[1];
		if ( num % 2 == 0) // se pkg.N par
		{
			frame[2] = 0x00;	
		}
		else
		{
			frame[2] = 0x40;	
		}
	}
	else // pacote de controlo
	{
		frame[2] = 0x00;
	}
	
	// bcc1
	frame[3] = (frame[1] ^ frame[2]);

	int i;
	int b = 4;
	
	for (i = 0; i <= size; i++)
	{	
		if (pkg[i] == ESC) // ESC
		{
			frame[b] = ESC;
			b++;
			frame[b] = 0x5d;
			b++;
		}
		else
		{
			if (pkg[i] == FLAG) // FLAG
			{
				frame[b] = ESC;
				b++;
				frame[b] = 0x5e;
				b++;
			}
			else
			{
				frame[b] = pkg[i];
				b++;
			}
		}
	
		// stuffing
		// trama[i + 4] = pkg[i];
	}
	i = 5 + size;
		
	// bcc2
	frame[b] = xor(pkg, 0, (size+0));
	b++;
	frame[b] = FLAG;
	b++;

	//printf("Tamanho trama I: %d\n", (*tamTrama));

	//verDados(trama, *tamTrama);

	//frameUnbuilderI(trama, tamTrama);
	
	//printf("[0x%X, 0x%X, 0x%X, 0x%X, ..., 0x%X, 0x%X]\n", trama[0], trama[1], trama[2], trama[3], trama[(*tamTrama)-1], trama[(*tamTrama)]);
	
	return(b - 1);
}

int suFrame(int emissor, int numSeq, int qualC, unsigned char frame[MTS])
{
	//printf("-------------------------\nFRAME SU BUILDER\n-------------------------\n");
	limparFrame(frame);
	
	frame[0] = FLAG;
	
	switch(qualC)
	{
		case 0: // SET -> comando
			frame[2]	= 0x03;
			frame[1] = (emissor == 1) ? 0x03 : 0x01;
			break;
		case 1: // DISC -> comando
			frame[2]	= 0x0b;
			frame[1] = (emissor == 1) ? 0x03 : 0x01;		
			break;
		case 2: // UA -> resposta
			frame[2]	= 0x07;
			frame[1] = (emissor == 1) ? 0x01 : 0x03;		
			break;
		case 3: // RR -> resposta
			if ((numSeq % 2) == 0)
			{
				frame[2]	= 0x85;
			}
			else
			{
				frame[2]	= 0x05;			
			}
			frame[1] = (emissor == 1) ? 0x01 : 0x03;		
			break;
		case 4: // REJ -> resposta
			if ((numSeq % 2) == 0)
			{
				frame[2]	= 0x81;
			}
			else
			{
				frame[2]	= 0x01;			
			}
			frame[1] = (emissor == 1) ? 0x01 : 0x03;		
			break;
	}
	frame[3] = (frame[1] ^ frame[2]);
	frame[4] = FLAG;

	//printf("[0x%X, 0x%X, 0x%X, 0x%X, 0x%X]\n", trama[0], trama[1], trama[2], trama[3], trama[4]);
	
	//verDados(trama, 5);
	
	return(5);
}


void packageToControl(unsigned char pkg[MFS + 10], int size, char * fileName, int * tamFile)
{
	//printf("-------------------------\nCONTROL UNPACKET\n-------------------------\n");
	
	//printf("SIZE: %d\n", size);
	
	unsigned char C = pkg[0];
	unsigned char T1 = 0x00, T2 = 0x00;
	int vec1 = 0, vec2 = 0;

	int tamanhoTotal = 0;

	(*tamFile) = 0;

	unsigned char nomeFicheiro[255];

	int i = 0, tf = 0, tn = 0;
	int ref = 0;

	T1 = pkg[1];
	vec1 = (int) pkg[2];
	
	ref = 3;
	for (i = 0; i < vec1; i++)
	{
		int t = (int) pkg[i + ref];
		(*tamFile) = (*tamFile) * 10 + t;
	}
	
	ref += vec1;
	T2 = pkg[ref];
	vec2 = (int) pkg[ref+1];
	ref += 2;
 
	for (i = 0; i < vec2; i++)
	{
		fileName[i] = (char)pkg[i + ref];
	}
	fileName[vec2] = '\0';
	
	//printf("[0x%X, 0x%X, %d, ..., 0x%X, %d, ...]\n\n", C, T1, vec1, T2, vec2);
	//printf("Tamanho do ficheiro: %d bytes\n", tamFicheiro);
	//printf("Nome do ficheiro: %s\n", nomeFicheiro);

	// armazenar tamanho e nome do ficheiro no lado do llread() 
}

int controlToPackage( char * nomeFicheiro, int tamFicheiro, int modo, unsigned char pkg[MFS + 10])
{
	//controlPacket(int modo, char * str_file, int tam_file)

	//printf("===========================\nCONTROL PACKET\n-------------------------\n");
	int comprimentoFile = strlen(nomeFicheiro);
	int comprimentoTamanho = numDigitos(tamFicheiro);

	int i, j;
	int total =
		1 +
		1 + 1 + comprimentoFile + 
		1 + 1 + comprimentoTamanho;	

	limparPacote(pkg);
	
	i = 0;
	if (modo == 2) // 0x01 -> inicio de transmissao
	{
		pkg[i] = 0x02;
		i++;
	}
	else if (modo == 3)  // 0x02 -> fim de transmissao
	{
		pkg[i] = 0x03;
		i++;
	}

	//printf("[0x%X, ", pkg[i-1]);	
	
	pkg[i] = 0x00; // tamanho do ficheiro
	i++;

	//printf("0x%X, ", pkg[i-1]);

	pkg[i] = (char) comprimentoTamanho;
	i++;
	
	//printf("%d, ", comprimentoTamanho);

	char * s = toString(tamFicheiro);

	for (j = 0; j < comprimentoTamanho; j++)
	{
		pkg[i] = s[j];
		i++;
	}

	pkg[i] = 0x01; // nome do ficheiro
	i++;

	//printf("..., 0x%X, ", pkg[i-1]);

	pkg[i] = (unsigned char) comprimentoFile;
	i++;

	for (j = 0; j < comprimentoFile; j++)
	{
		pkg[i] = nomeFicheiro[j];
		
		i++;
	}
	
	//printf("%d, ...]\n", j);

	//printf("Tamanho do pacote: %d\n\n", *tamPacote - 1);
		
	return(i - 1);
}

int packageToData(unsigned char pkg[MFS + 10], int size, unsigned char data[MFS + 1])
{
	//printf("-------------------------\nDATA UNPACKET\n-------------------------\n");
	
	//printf("Tamanho do pacote: %d\n", size);
	//verDados(pkg, size);
	
	limparDados(data);
	
	unsigned char C = pkg[0];
	unsigned char N = pkg[1];

	unsigned char L2 = pkg[2];
	unsigned char L1 = pkg[3];

	int i = 4, j = 0;

	int NN = N;
	int LL2 = (int) L2;
	int LL1 = (int) L1;

	//printf("[C, N, L2, L1]: [0x%X, 0x%X, 0x%X, 0x%X]\n", C, NN, LL2, LL1);
	
	int tamFragmento = LL2*MFS + LL1;
	int tt = size - 4;

	//printf("Tamanho do fragmento (aS): %d\n", tt);
	//printf("Tamanho do fragmento teorico (LL2*MFS + LL1): %d\n", tamFragmento);

	for (i = 4; i <= size; i++)
	{
		data[j] = pkg[i];
		j++;
	}
	
	//printf("Tamanho do fragmento: %d\n\n", (*tamFrag));
	
	//verDados(data, *tamFrag);
	
	return(j - 1);
}

int dataToPackage(unsigned char data[MFS+1], int numSeq, int size, unsigned char pkg[MFS + 10])
{
	//printf("===========================\nDATA PACKET\n-------------------------\n");
	//printf("Tamanho do fragmento: %d\n", size);
	//verDados(frag, size);
	
	unsigned char C = Cpkg_dados;
	unsigned char N = numSeq;

	//verDados(frag, size+1);

	int LL2 = size / MFS;
	int LL1 = size - LL2 * MFS;
	unsigned char L2 = (char)(LL2);
	unsigned char L1 = (char)(LL1);
	
	//printf("[C, N, L2, L1]: [0x%X, 0x%X, 0x%X, 0x%X]\n", C, N, L2, L1);

	limparPacote(pkg);
	
	int a, b = 4;
	
	pkg[0] = C;
	pkg[1] = N;
	pkg[2] = L2;
	pkg[3] = L1;

	for (a = 0; a <= size; a++)
	{
		pkg[b] = data[a];
		b++;
	}
	
	//printf("PKG[ultimo]: 0x%X\n\n", pkg[b-1]);
		
	//printf("Tamanho do pacote: %d\n", *tamPacote);
	
	//for(b = 0; b < *tamPacote; b++)
	//{
		//printf("0x%X ", pacote[b]);
		//if (b % 10 == 0)
			//printf("\n");
	//} printf("\n\n");
	
	//verDados(pkg, *tamPacote) ;
	
	return(b - 1);
}

#endif
