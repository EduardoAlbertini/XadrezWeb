function addQuad(x,y,c)
{
	var ncubo = new GLGE.Object();
	ncubo.setMesh(doc.getElement("MCubo"));
	if(c == "B"){
		ncubo.setMaterial(doc.getElement("branco"));
		//ncubo.setPickable(true);
	}
	else
		ncubo.setMaterial(doc.getElement("preto"));
	ncubo.setScaleX(2);
	ncubo.setScaleY(2);
	ncubo.setScaleZ(0.1);
	ncubo.setId("Quad"+numQuad);
	ncubo.setLocX(x);
	ncubo.setLocY(y);
	ncubo.setLocZ(1);
	numQuad++;
	
	jogoCena.addObject(ncubo);
	return ncubo;

}
function addPeca(x,y,c)
{
	//var ncubo = new GLGE.Object();
	//ncubo.setMesh(doc.getElement("MPeca"));
	var ncubo = new GLGE.Wavefront();
	if(c == "B")
		ncubo.setSrc("pecas/peaoB.obj");
	else
		ncubo.setSrc("pecas/peaoP.obj");
	ncubo.setScaleX(2);
	ncubo.setScaleY(2);
	ncubo.setScaleZ(2);
	ncubo.setId("PN"+numQuad+c);
	ncubo.setLocX(x);
	ncubo.setLocY(y);
	ncubo.setLocZ(1);
	numQuad++;
	
	jogoCena.addObject(ncubo);
	return ncubo;

}
function addPecaX(x,y,c,p)
{
	//var ncubo = new GLGE.Object();
	//ncubo.setMesh(doc.getElement("MPeca"));
	var ncubo = new GLGE.Wavefront();
	var src = "pecas/"+p+".obj";
	
	ncubo.setSrc(src);
	ncubo.setScaleX(2);
	ncubo.setScaleY(2);
	ncubo.setScaleZ(2);
	ncubo.setId("PN"+numQuad+c);
	ncubo.setLocX(x);
	ncubo.setLocY(y);
	ncubo.setLocZ(1);
	numQuad++;
	
	jogoCena.addObject(ncubo);
	return ncubo;

}

function InitTabu()
{
	for(var i = 0;i < 8; i++)
		tabuleiro[i] = new Array(8);
	for(var i = 0;i < 8; i++)
		tabuleiroQuad[i] = new Array(8);

	//Coloca os quadrados pretos e brancos no tabuleiro
	
	var x = -14;
	var y = -15;
	var k = 7;
	var l = 0;
	for(var i=0;i<4;i++)
	{
		for(var j=0;j<4;j++)
		{
			
			tabuleiroQuad[k][l] = addQuad(x,y,"P");
			x+=8;
			l+=2;
		}
		k -= 2;
		l = 0;
		x = -14;
		y+=8;
	}
	x = -10;
	y = -11;
	k = 6;
	l = 1;
	for(var i=0;i<4;i++)
	{
		for(var j=0;j<4;j++)
		{
			
			tabuleiroQuad[k][l] = addQuad(x,y,"P");
			x+=8;
			l+=2;
			
		}
		k -=2;
		l = 1;
		x = -10;
		y+=8;
	}
	x = -10;
	y = -15;
	k = 7;
	l = 1;
	
	for(var i=0;i<4;i++)
	{
		for(var j=0;j<4;j++)
		{
			
			tabuleiroQuad[k][l] = addQuad(x,y,"B");
			x+=8;
			l+=2;
			
			
		}
		l=1;
		k -=2;
		x = -10;
		y+=8;
	}
	x = -14;
	y = -11;
	k = 6;
	l = 0;
	for(var i=0;i<4;i++)
	{

		for(var j=0;j<4;j++)
		{
			tabuleiroQuad[k][l] = addQuad(x,y,"B");
			x+=8;
			l+=2;
		}
		l = 0;
		k -=2;
		x = -14;
		y+=8;
	}
	//---------------------------------------------------------
	//---------------------------------------------------------
	//------------Coloca as pecas no tabuleiro-----------------
	//Pecas pretas
	for(var i=0;i<8;i++)
	{
		for(var j=0;j<8;j++)
		{
			tabuleiro[i][j] = 0;
		
		}
	}
	/*
	x = -14;
	y = -15;
	for(var i=0;i<8;i++)
	{	
		tabuleiro[7][i] = addPeca(x,y,"P");
		x+=3.95;
	}
	*/
	x = -14;
	y = 9;
	for(var i=0;i<8;i++)
	{	
		tabuleiro[1][i] = addPeca(x,y,"P");
		x+=3.95;
	}
	
	//TORRE Preto
	x = -14;
	y = 13;
	
	tabuleiro[0][0] = addPecaX(x,y,"P","torreP");
	x = 14;
	tabuleiro[0][7] = addPecaX(x,y,"P","torreP");
	//FIM TORRE
	//CAVALO Preto
	x = -10;
	y = 13;
	
	tabuleiro[0][1] = addPecaX(x,y,"P","cavaloP");
	tabuleiro[0][1].setRotZ(1.57);
	x = 10;
	tabuleiro[0][6] = addPecaX(x,y,"P","cavaloP");
	tabuleiro[0][6].setRotZ(1.57);
	//FIM CAVALO

	//Pispo Preto
	x = -6;
	y = 13;
	
	tabuleiro[0][2] = addPecaX(x,y,"P","bispoP");
	x = 6;
	tabuleiro[0][5] = addPecaX(x,y,"P","bispoP");
	
	//FIM Pispo

	//Pispo Rei e Rainha
	x = -2;
	y = 13;
	
	tabuleiro[0][3] = addPecaX(x,y,"P","rainhaP");
	x = 2;
	tabuleiro[0][4] = addPecaX(x,y,"P","reiP");
	
	//FIM Rei rainha


	//Pecas Brancas	
	
	//TORRE Branca
	x = -14;
	y = -15.5;
	
	tabuleiro[7][0] = addPecaX(x,y,"B","torreB");
	x = 14;
	tabuleiro[7][7] = addPecaX(x,y,"B","torreB");
	//FIM TORRE
	//CAVALO Branca
	x = -10;
	y = -15;
	
	tabuleiro[7][1] = addPecaX(x,y,"B","cavaloB");
	tabuleiro[7][1].setRotZ(-1.57);
	x = 10;
	tabuleiro[7][6] = addPecaX(x,y,"B","cavaloB");
	tabuleiro[7][6].setRotZ(-1.57);
	//FIM CAVALO

	//Bispo Branca
	x = -6;
	y = -15;
	
	tabuleiro[7][2] = addPecaX(x,y,"B","bispoB");
	x = 6;
	tabuleiro[7][5] = addPecaX(x,y,"B","bispoB");
	
	//FIM Bispo

	//Bispo Rei e Rainha
	x = -2;
	y = -15;
	
	tabuleiro[7][3] = addPecaX(x,y,"B","rainhaB");
	x = 2;
	tabuleiro[7][4] = addPecaX(x,y,"B","reiB");
	
	//FIM Rei rainha

	
	x = -14;
	y = -11;
	for(var i=0;i<8;i++)
	{	
		tabuleiro[6][i] = addPeca(x,y,"B");
		x+=3.95;
	}
/*	x = -9;
	y = 2;
	for(var i=1;i<8;i+=2)
	{	
		tabuleiro[2][i] = addPeca(x,y,"B");
		x+=8;
	}
	x = -10;
	y = 11;
*/
	//-----------------------------------------------------
	//-----------------------------------------------------	
}
function inicio()
{
	if(online){
		tcpEnvia("I");
	}
	location.href = "index.html";	
}
