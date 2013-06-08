var hoverobj;
var mouseovercanvas;
var pecaPega;
var ThreadViraTabu;

function Pega(mouse)
{
	var obj;
	var mousepos=mouse.getMousePosition();
	if(mouseovercanvas){
		mousepos.x=mousepos.x-document.getElementById("container").offsetLeft;
		mousepos.y=mousepos.y-document.getElementById("container").offsetTop;
		if(mousepos.x && mousepos.y){
			obj=jogoCena.pick(mousepos.x,mousepos.y).object;
				if(obj && obj!=hoverobj){
						obj.oldmaterial=obj.getMaterial();
						obj.setMaterial(doc.getElement("verde"));
						VerificaPeca(obj);
								
				}
			if(hoverobj) hoverobj.setMaterial(hoverobj.oldmaterial);		
			hoverobj=obj;
			document.getElementById("debug2").innerHTML = "P: "+numPecaP+" B: "+numPecaB; 
		}
	}
}

function VerificaPeca(obj)
{
	var dir;
	var posP;
	var posQ;


	if(obj.id[0] == "P")//Primeiro pega a peça
		pecaPega = obj;
	else
		if(pecaPega && obj.id[0] == "Q" )//Segundo Pega o futuro local
		{		
			posQ = PegaQuadTabuleiro(obj);
			posP = PegaPecaTabuleiro(pecaPega);

			tcpEnvia(posP.li.toString()+posP.co.toString()+posQ.li.toString()+posQ.co.toString());
			return;
		}

	
}
function Ganhador()
{
	if(numPecaP == 0 && numPecaB > 1)
	{
		document.getElementById("vez").innerHTML = "Jogador 2 GANHOU!!";
		document.getElementById("vez").style.width = "700";
		document.getElementById("vez").style.height = "540";
		document.getElementById("vez").style.color = "rgb(30,66,17)";
		document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
		document.getElementById("vez").style.marge = "auto";
		document.getElementById("vez").style.fontSize = "200%";
	}else{
			if(numPecaB == 0 && numPecaP > 1)
			{
				document.getElementById("vez").innerHTML = "Jogador 1 GANHOU!!";
				document.getElementById("vez").style.width = "700";
				document.getElementById("vez").style.height = "540";
				document.getElementById("vez").style.color = "rgb(30,66,17)";
				document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
				document.getElementById("vez").style.marge = "auto";
				document.getElementById("vez").style.fontSize = "200%";
			}
			else{
				if(numPecaB == 1 && numPecaP == 1)
				{
					document.getElementById("vez").innerHTML = "Empate =D!!";
					document.getElementById("vez").style.width = "700";
					document.getElementById("vez").style.height = "540";
					document.getElementById("vez").style.color = "rgb(30,66,17)";
					document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
					document.getElementById("vez").style.marge = "auto";
					document.getElementById("vez").style.fontSize = "200%";
				}
			}
				
		}
		
}
function ViraTabuleiroD()
{
	camx+=0.2;
	//document.getElementById("debug").innerHTML = camx;
	if(camx >= 31)
	{
		window.clearInterval(ThreadViraTabu);
		ThreadViraTabu = null;
		gira = false;
		
	}
}
function ViraTabuleiroE()
{
	camx-=0.2;
	//document.getElementById("debug").innerHTML = camx;
	if(camx <= 0)
	{
		window.clearInterval(ThreadViraTabu);
		ThreadViraTabu = null;
		gira = false;

	}
}

function PegaPecaTabuleiro(obj)
{
	for(var i = 0;i<8;i++)
		for(var j = 0;j<8;j++){
				if(obj.id == tabuleiro[i][j].id)
				{
					return {li:i,co:j};
				}
		}
	return null;
}
function PegaQuadTabuleiro(obj)
{
	
	for(var i = 0;i<8;i++)
		for(var j = 0;j<8;j++){		
				if(obj.id == tabuleiroQuad[i][j].id)
				{				
					return {li:i,co:j};
				}
		}
	return null;
}
function MovePecaOnline(pos)
{
	var obj;

		pos = pos.split("$");
		obj = tabuleiro[pos[1]][pos[2]];
		if(obj != 0)
		{
			tabuleiro[pos[1]][pos[2]] = 0;
			tabuleiro[pos[3]][pos[4]] = obj;
			tabuleiro[pos[3]][pos[4]].blendTo({LocX:(pos[5]),LocY:(pos[6])},1000);
			if(pos[0] == "C" || pos[0] == "CS")
			{
				tabuleiro[pos[7]][pos[8]].blendTo({LocX:-18,LocY:0},1000);
				tabuleiro[pos[7]][pos[8]] = 0;
				if(jogador2)
					numPecaB--;
				else
					numPecaP--;
			}
			VerificaDama(tabuleiro[pos[3]][pos[4]]);
			return true;
		}
		else
			return false;
	
}


function mudaAvisaVez()
{
	if(play1 && !jogador2){
		document.getElementById("vez").innerHTML = "Jogador 1";
		document.getElementById("vez").style.color = "white";
		document.getElementById("vez").style.backgroundColor = "rgba(247,24,10,0.5)";
		
	}
	if(!play1 && !jogador2){
		document.getElementById("vez").innerHTML = "Jogador 2";
		document.getElementById("vez").style.color = "rgb(30,66,17)";
		document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
	}
	if(play1 && jogador2){
		document.getElementById("vez").innerHTML = "Jogador 1";
		document.getElementById("vez").style.color = "white";
		document.getElementById("vez").style.backgroundColor = "rgba(247,24,10,0.5)";
	}
	if(!play1 && jogador2){
		document.getElementById("vez").innerHTML = "Jogador 2";
		document.getElementById("vez").style.color = "rgb(30,66,17)";
		document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
	}
}
function Ganhador()
{
	if(numPecaP == 0 && numPecaB > 1)
	{
		document.getElementById("vez").innerHTML = "Jogador 2 GANHOU!!";
		document.getElementById("vez").style.width = "700";
		document.getElementById("vez").style.height = "540";
		document.getElementById("vez").style.color = "rgb(30,66,17)";
		document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
		document.getElementById("vez").style.marge = "auto";
		document.getElementById("vez").style.fontSize = "200%";
	}else{
			if(numPecaB == 0 && numPecaP > 1)
			{
				document.getElementById("vez").innerHTML = "Jogador 1 GANHOU!!";
				document.getElementById("vez").style.width = "700";
				document.getElementById("vez").style.height = "540";
				document.getElementById("vez").style.color = "rgb(30,66,17)";
				document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
				document.getElementById("vez").style.marge = "auto";
				document.getElementById("vez").style.fontSize = "200%";
			}
			else{
				if(numPecaB == 1 && numPecaP == 1)
				{
					document.getElementById("vez").innerHTML = "Empate =D!!";
					document.getElementById("vez").style.width = "700";
					document.getElementById("vez").style.height = "540";
					document.getElementById("vez").style.color = "rgb(30,66,17)";
					document.getElementById("vez").style.backgroundColor = "rgba(255,255,255,0.5)";
					document.getElementById("vez").style.marge = "auto";
					document.getElementById("vez").style.fontSize = "200%";
				}
			}
				
		}
		
}
function Estado()
{
	if(!online)
	{
		document.getElementById("estado").innerHTML = "REDE OFFLINE";
		document.getElementById("estado").style.backgroundColor = "rgba(255,255,255,0.5)";
	}
	else{
		if(document.getElementById("estado").innerHTML == "Conectado")
			document.getElementById("estado").style.backgroundColor = "rgba(30,66,17,0.5)";
		else
			document.getElementById("estado").style.backgroundColor = "rgba(247,24,10,0.5)";
	}
}
