#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

char tabuleiro[8][8];
char jogador_ativo = 'B'; // B => Brancas (maiúscula) | P => Pretas (minúscula)

char limpa_tabuleiro()
{
    int i, j;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            tabuleiro[i][j] = ' ';
}

char mostra_tabuleiro()
{
    int i, j;
    printf("\nTabuleiro:\n\n");
    printf("  ");
    for (i = 0; i < 8; ++i)
        printf(" %d  ", i+1);
    printf("\n");
    for (i = 0; i < 8; ++i)
    {
        printf("%d |", i+1);
        for (j = 0; j < 8; ++j)
            printf("%c | ", tabuleiro[i][j]);
        printf("\n\n");
    }
}

bool lim_tab(int l, int c)
{
    if (l < 0 || c < 0) 
		return false;
		
    return (l % 8 ==  l) && (c % 8 == c) ? true : false;
}

int faixa_jogador(char x)
{
	int p = x;
	if (p >= 97 && p <= 122)
		return 1; // a
	else if (p >= 65 && p <= 90)
		return 2; // A
	else
		return -1;
}

char peca_do_adversario(int l, int c, int l_dest, int c_dest)
{
	if (faixa_jogador(tabuleiro[l][c]) == faixa_jogador(tabuleiro[l_dest][c_dest]))
		return '*';
	else
		return tabuleiro[l_dest][c_dest];
}

char peca_do_adversario_peao(int l, int c, int l_dest, int c_dest)
{
	printf("\n PEAO %d %d %d %d\n",l,c,l_dest, c_dest );
	if (faixa_jogador(tabuleiro[l][c]) == faixa_jogador(tabuleiro[l_dest][c_dest]) || tabuleiro[l_dest][c_dest] == ' ')
		return '*';
	else
		return tabuleiro[l_dest][c_dest];
}

bool vm_peao(int l, int c, int l_dest, int c_dest)
{
    if (jogador_ativo == 'B')
    {
        if (tabuleiro[6][c] == 'P')
            if (tabuleiro[l-2][c] == ' '  && lim_tab(l-2, c))
                if (l-2 == l_dest && c == c_dest) return true;

        if (tabuleiro[l-1][c] == ' '  && lim_tab(l-1, c))
            if (l-1 == l_dest && c == c_dest) return true;
        if (tabuleiro[l-1][c-1] == peca_do_adversario_peao(l, c, l-1, c-1) && lim_tab(l-1, c-1))
            if (l-1 == l_dest && c-1 == c_dest) return true;
        if (tabuleiro[l-1][c+1] == peca_do_adversario_peao(l, c, l-1, c+1) && lim_tab(l-1, c+1))
            if (l-1 == l_dest && c+1 == c_dest) return true;
    }
    
    if (jogador_ativo == 'P')
    {
        if (tabuleiro[1][c] == 'p')
            if (tabuleiro[l+2][c] == ' '  && lim_tab(l+2, c))
                if (l+2 == l_dest && c == c_dest) return true;

        if (tabuleiro[l+1][c] == ' '  && lim_tab(l+1, c))
            if (l+1 == l_dest && c == c_dest) return true;
        if (tabuleiro[l+1][c+1] == peca_do_adversario_peao(l, c, l+1, c+1) && lim_tab(l+1, c+1))
            if (l+1 == l_dest && c+1 == c_dest) return true;
        if (tabuleiro[l+1][c-1] == peca_do_adversario_peao(l, c, l+1, c-1) && lim_tab(l+1, c-1))
            if (l+1 == l_dest && c-1 == c_dest) return true;
    }
    
	return false;
}

bool vm_torre(int l, int c, int l_dest, int c_dest)
{
    int i;

    for (i = l-1; i >= 0; --i)
        if (peca_do_adversario(l, c, i, c) == '*') // Encontrou uma peça que não é do adversário
            break;
        else if (tabuleiro[i][c] == ' ' && i == l_dest && c == c_dest) // Encontrei um espaço e é pra onde eu quero mover
            return true;
        else if (tabuleiro[i][c] == peca_do_adversario(l, c, i, c) && i == l_dest && c == c_dest) 
			return true;
	
    for (i = l+1; i < 8; ++i)
        if (peca_do_adversario(l, c, i, c) == '*') // Encontrou uma peça que não é do adversário
            break;
        else if (tabuleiro[i][c] == ' ' && i == l_dest && c == c_dest) // Encontrei um espaço e é pra onde eu quero mover
            return true;
        else if (tabuleiro[i][c] == peca_do_adversario(l, c, i, c) && i == l_dest && c == c_dest) 
			return true;
	
    for (i = c-1; i >= 0; --i)
        if (peca_do_adversario(l, c, l, i) == '*')
            break;
        else if (tabuleiro[l][i] == ' ' && l == l_dest && i == c_dest)
            return true;
        else if (tabuleiro[l][i] == peca_do_adversario(l, c, l, i) && l == l_dest && i == c_dest)
            return true;

    for (i = c+1; i < 8; ++i)
        if (peca_do_adversario(l, c, l, i) == '*')
            break;
        else if (tabuleiro[l][i] == ' ' && l == l_dest && i == c_dest)
            return true;
        else if (tabuleiro[l][i] == peca_do_adversario(l, c, l, i) && l == l_dest && i == c_dest)
            return true;
	
	return false;
}

bool vm_bispo(int l, int c, int l_dest, int c_dest)
{
    int i, j;
	
    for (i = l+1, j = c+1; i < 8; ++i, ++j)
    {
        if (!lim_tab(i, j)) break;
        
        if (peca_do_adversario(l, c, i, j) == '*')
            break;
        else if (tabuleiro[i][j] == ' ' && i == l_dest && j == c_dest)
            return true;
        else if (tabuleiro[i][j] == peca_do_adversario(l, c, i, j) && i == l_dest && j == c_dest)
            return true;
    }
	
    for (i = l-1, j = c-1; i >= 0; --i, --j)
    {
        if (!lim_tab(i, j)) break;
        
        if (peca_do_adversario(l, c, i, j) == '*')
            break;
        else if (tabuleiro[i][j] == ' ' && i == l_dest && j == c_dest)
            return true;
        else if (tabuleiro[i][j] == peca_do_adversario(l, c, i, j) && i == l_dest && j == c_dest)
            return true;
    }
	
    for (i = l-1, j = c+1; i >= 0; --i, j++)
    {
        if (!lim_tab(i, j)) break;
        
        if (peca_do_adversario(l, c, i, j) == '*')
            break;
        else if (tabuleiro[i][j] == ' ' && i == l_dest && j == c_dest)
            return true;
        else if (tabuleiro[i][j] == peca_do_adversario(l, c, i, j) && i == l_dest && j == c_dest)
            return true;
    }
	
    for (i = l+1, j = c-1; i < 8; ++i, j--)
    {
        if (!lim_tab(i, j)) break;
        
        if (peca_do_adversario(l, c, i, j) == '*')
            break;
        else if (tabuleiro[i][j] == ' ' && i == l_dest && j == c_dest)
            return true;
        else if (tabuleiro[i][j] == peca_do_adversario(l, c, i, j) && i == l_dest && j == c_dest)
            return true;
    }
	
	return false;
}

bool vm_cavalo(int l, int c, int l_dest, int c_dest)
{
    if (lim_tab(l-2, c-1))
        if (tabuleiro[l-2][c-1] == ' ' || tabuleiro[l-2][c-1] == peca_do_adversario(l, c, l-2, c-1) )
			if (l-2 == l_dest && c-1 == c_dest)
				return true;
			
    if (lim_tab(l-2, c+1))
        if (tabuleiro[l-2][c+1] == ' ' || tabuleiro[l-2][c+1] == peca_do_adversario(l, c, l-2, c+1) )
			if (l-2 == l_dest && c+1 == c_dest)
				return true;
			
    if (lim_tab(l+2, c-1))    
        if (tabuleiro[l+2][c-1] == ' ' || tabuleiro[l+2][c-1] == peca_do_adversario(l, c, l+2, c-1) )
            if (l+2 == l_dest && c-1 == c_dest)
				return true;

    if (lim_tab(l+2, c+1))
        if (tabuleiro[l+2][c+1] == ' ' || tabuleiro[l+2][c+1] == peca_do_adversario(l, c, l+2, c+1) )
			if (l+2 == l_dest && c+1 == c_dest)
				return true;
			
    if (lim_tab(l-1, c-2))
        if (tabuleiro[l-1][c-2] == ' ' || tabuleiro[l-1][c-2] == peca_do_adversario(l, c, l-1, c-2) )
			if (l-1 == l_dest && c-2 == c_dest)
				return true;
			
    if (lim_tab(l+1, c-2))
        if (tabuleiro[l+1][c-2] == ' ' || tabuleiro[l+1][c-2] == peca_do_adversario(l, c, l+1, c-2) )
            if (l+1 == l_dest && c-2 == c_dest)
				return true;

    if (lim_tab(l-1, c+2))    
        if (tabuleiro[l-1][c+2] == ' ' || tabuleiro[l-1][c+2] == peca_do_adversario(l, c, l-1, c+2) )
            if (l-1 == l_dest && c+2 == c_dest)
				return true;
			
    if (lim_tab(l+1, c+2))
        if (tabuleiro[l+1][c+2] == ' ' || tabuleiro[l+1][c+2] == peca_do_adversario(l, c, l+1, c+2) )
            if (l+1 == l_dest && c+2 == c_dest)
				return true;
				
	return false;
}

bool vm_rei(int l, int c, int l_dest, int c_dest)
{
    if ((tabuleiro[l][c+1] == ' ' || tabuleiro[l][c+1] == peca_do_adversario(l, c, l, c+1)) && lim_tab(l, c+1))
		if (l == l_dest && c+1 == c_dest)
			return true;
		
    if ((tabuleiro[l][c-1] == ' ' || tabuleiro[l][c-1] == peca_do_adversario(l, c, l, c-1)) && lim_tab(l, c-1))
		if (l == l_dest && c-1 == c_dest)
			return true;
		
    if ((tabuleiro[l-1][c+1] == ' ' || tabuleiro[l-1][c-1] == peca_do_adversario(l, c, l-1, c+1)) && lim_tab(l-1, c+1))
		if (l-1 == l_dest && c+1 == c_dest)
			return true;
		
    if ((tabuleiro[l-1][c-1] == ' ' || tabuleiro[l-1][c-1] == peca_do_adversario(l, c, l-1, c-1)) && lim_tab(l-1, c-1))
		if (l-1 == l_dest && c-1 == c_dest)
			return true;
		
    if ((tabuleiro[l-1][c] == ' ' || tabuleiro[l-1][c] == peca_do_adversario(l, c, l-1, c)) && lim_tab(l-1, c))
		if (l-1 == l_dest && c == c_dest)
			return true;
		
    if ((tabuleiro[l+1][c+1] == ' ' || tabuleiro[l+1][c-1] == peca_do_adversario(l, c, l+1, c-1)) && lim_tab(l+1, c+1))
		if (l+1 == l_dest && c+1 == c_dest)
			return true;
		
    if ((tabuleiro[l+1][c-1] == ' ' || tabuleiro[l+1][c-1] == peca_do_adversario(l, c, l+1, c-1)) && lim_tab(l+1, c-1))
		if (l+1 == l_dest && c-1 == c_dest)
			return true;
		
    if ((tabuleiro[l+1][c] == ' ' || tabuleiro[l+1][c] == peca_do_adversario(l, c, l+1, c)) && lim_tab(l+1, c))
		if (l+1 == l_dest && c == c_dest)
			return true;
			
	return false;
}

bool vm_dama(int l, int c, int l_dest, int c_dest)
{
    if (vm_torre(l, c, l_dest, c_dest) || vm_bispo(l, c, l_dest, c_dest))
		return true;
	else
		return false;
}

void rotaciona_tabuleiro()
{
	char temp[8][8], i, j;
	
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			temp[7 - i][j] = tabuleiro[i][j];

	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			tabuleiro[i][j] = temp[i][j];
}

// Verifica Movimentos
bool vm(int l, int c, int l_dest, int c_dest)
{
    // Pretas  => a : 1
    // Brancas => A : 2
    if(jogador_ativo == 'P' && faixa_jogador(tabuleiro[l][c]) == 2)
        return false;

    if (tabuleiro[l][c] == 'P' || tabuleiro[l][c] == 'p')
        if(vm_peao(l, c, l_dest, c_dest))
		{
			tabuleiro[l_dest][c_dest] = tabuleiro[l][c];
			tabuleiro[l][c] = ' ';
			//rotaciona_tabuleiro();
            jogador_ativo = jogador_ativo == 'B' ? 'P' : 'B';
            return true;
		}
		else
			return false;
			
    if (tabuleiro[l][c] == 'T' || tabuleiro[l][c] == 't')
        if (vm_torre(l, c, l_dest, c_dest))
		{
			tabuleiro[l_dest][c_dest] = tabuleiro[l][c];
			tabuleiro[l][c] = ' ';
			//rotaciona_tabuleiro();
            jogador_ativo = jogador_ativo == 'B' ? 'P' : 'B';
            return true;
		}
		else
			return false;
			
    if (tabuleiro[l][c] == 'B' || tabuleiro[l][c] == 'b')
        if (vm_bispo(l, c, l_dest, c_dest))
		{
			tabuleiro[l_dest][c_dest] = tabuleiro[l][c];
			tabuleiro[l][c] = ' ';
			//rotaciona_tabuleiro();
			jogador_ativo = jogador_ativo == 'B' ? 'P' : 'B';
            return true;
		}
		else
			return false;
			
    if (tabuleiro[l][c] == 'C' || tabuleiro[l][c] == 'c')
        if (vm_cavalo(l, c, l_dest, c_dest))
		{
			tabuleiro[l_dest][c_dest] = tabuleiro[l][c];
			tabuleiro[l][c] = ' ';
			//rotaciona_tabuleiro();
			jogador_ativo = jogador_ativo == 'B' ? 'P' : 'B';
            return true;
		}
		else
			return false;
		
    if (tabuleiro[l][c] == 'R' || tabuleiro[l][c] == 'r')
        if (vm_rei(l, c, l_dest, c_dest))
		{
			tabuleiro[l_dest][c_dest] = tabuleiro[l][c];
			tabuleiro[l][c] = ' ';
			//rotaciona_tabuleiro();
			jogador_ativo = jogador_ativo == 'B' ? 'P' : 'B';
            return true;
		}
		else
			return false;
			
    if (tabuleiro[l][c] == 'D' || tabuleiro[l][c] == 'd')
        if (vm_dama(l, c, l_dest, c_dest))
		{
			tabuleiro[l_dest][c_dest] = tabuleiro[l][c];
			tabuleiro[l][c] = ' ';
			//rotaciona_tabuleiro();
			jogador_ativo = jogador_ativo == 'B' ? 'P' : 'B';
            return true;
		}
		else
			return false;
    
    return false;
}

void inicia_tabuleiro()
{
	int i;
	
	limpa_tabuleiro();
	
	tabuleiro[0][0] = 't';
	tabuleiro[0][7] = 't';
	tabuleiro[0][1] = 'c';
	tabuleiro[0][6] = 'c';
	tabuleiro[0][2] = 'b';
	tabuleiro[0][5] = 'b';
	tabuleiro[0][3] = 'd';
	tabuleiro[0][4] = 'r';
	
	for (i = 0; i < 8; ++i)
		tabuleiro[1][i] = 'p';
		
		
	tabuleiro[7][0] = 'T';
	tabuleiro[7][7] = 'T';
	tabuleiro[7][1] = 'C';
	tabuleiro[7][6] = 'C';
	tabuleiro[7][2] = 'B';
	tabuleiro[7][5] = 'B';
	tabuleiro[7][3] = 'D';
	tabuleiro[7][4] = 'R';
	
	for (i = 0; i < 8; ++i)
		tabuleiro[6][i] = 'P';
		
}

/**
void o_jogo()
{
    int l, c, l_dest, c_dest;
	
	inicia_tabuleiro();
	
	do
	{
		mostra_tabuleiro();
		
		if (jogador_ativo == 'B')
			printf("============================\nJogador 1 (peças maiúsculas)\n============================\n");
		else
			printf("============================\nJogador 2 (peças minúsculas)\n============================\n");
		
		printf("Entre com as coordenadas (linha,coluna) da peca: ");
		do {
			scanf("%d,%d", &l, &c);
			--l; --c;
			if (tabuleiro[l][c] == ' ' || !lim_tab(l, c))
				printf("Coordenada Incorreta. Tente outra vez: ");
		} while (tabuleiro[l][c] == ' ' || !lim_tab(l, c));
	
		printf("Entre com as coordenadas (linha,coluna) do destino: ");
		do {
			scanf("%d,%d", &l_dest, &c_dest);
			--l_dest; --c_dest;
			if (!lim_tab(l_dest, c_dest))
				printf("Coordenada Incorreta. Tente outra vez: ");
		} while (!lim_tab(l_dest, c_dest));
		
		vm(l, c, l_dest, c_dest);
	} while (true);
}

int main()
{
    srand(time(NULL));

    o_jogo();
	
    printf("\n=========================================\n");

    return 0;
}
*/