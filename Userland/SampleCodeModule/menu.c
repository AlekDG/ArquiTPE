#include <stdint.h>
#include <menu.h>
#include <consola.h>
#include <pepsiman.h>


void hoverOverOption(Option * option){option->isHovered=1;}
void deactivateHover(Option * option){option->isHovered=0;}

//USAR ESTA FUNCION PARA PASAR A LA SIGUIENTE FUNCION DEL MENU
void hoverOverNextoption(OptionMenu * optionMenu){

	//voy a iterar sobre el array de opciones para ver cual de todas esta ON
	//solo habra una a la vez
	for(int i=0; i<5; i++){
		if(optionMenu->options[i]->isHovered){
			deactivateHover(optionMenu->options[i]);
			if(i==4){   //estoy en la ultima, salto a la primera
				hoverOverOption(optionMenu->options[0]);
			}
			else{
				hoverOverOption(optionMenu->options[i+1]);  //resalto la primera
			}
			break;
		}
	}
	
	setXBuffer(50);
	setYBuffer(50);
	drawOptionMenuArray(optionMenu);   //tengo que volver a renderizar todo el menu
}

void hoverOverPreviousOption(OptionMenu * optionMenu){
	for(int i=0; i<5; i++){
		if(optionMenu->options[i]->isHovered){
			deactivateHover(optionMenu->options[i]);
			if(i==0){   //estoy en la primera, salto a la ultima
				hoverOverOption(optionMenu->options[4]);
			}
			else{
				hoverOverOption(optionMenu->options[i-1]);  //resalto la primera
				
			}
			break;
		}
	}
	setXBuffer(50);
	setYBuffer(50);
	drawOptionMenuArray(optionMenu);   //tengo que volver a renderizar todo el menu
	
}



//ESTO NO SE SI SE VA A USAR
void clickOption(Option * option){option->isClicked = 1;}
void unclickOption(Option * option){option->isClicked = 0;}

//todo

//drawTriangle(){funcion que dibuja la flechita de las opciones}

void drawOption(Option option, uint32_t * globalFGColor, int * globalXPos, int * globalYPos){
	setBGColor(WHITE);
	setFGColor(PEPSIBLUE);	//por seguridad
    int globalSize = getSize();
    uint32_t globalBGColor = getBGColor();
	uint32_t currentFG = getFGColor();
	int letterWidth = globalSize*8;
	int gap = 3 * globalSize;
	int borderHeight = option.borde.height * globalSize;
	int borderLength = option.borde.length * letterWidth;
	int borderThickness = option.borde.thickness * globalSize;
	

	//si esta hovereada tengo que cambiar el color del borde
	if(option.isHovered){
		*globalFGColor = RED;     //hacer un define de colores pls xD
	}

	//aca adentro asumo que tengo el buffer setedo correctamente, y voy a dibujar 
	//exactamente donde el recuadro
	drawRectangle(*globalFGColor, *globalXPos, *globalYPos,
	borderLength + (2*(borderThickness + gap)), 
	borderHeight + (2*(borderThickness + gap)));

	//empiezo a dibujar con offset de +thickness
	drawRectangle(globalBGColor, *globalXPos + borderThickness, *globalYPos + borderThickness,
	borderLength + (2*gap), 
	borderHeight + (2*gap));
	
	//desplazo el buffer de la esquina sup. izq. 
	//al centro del recuadro, para escribir la opcion
	*globalYPos += (borderThickness + gap);
	*globalXPos += (borderThickness + gap);	//dejo espacio de 3 letras
	//vuelvo a cambiar el color porque el texto deberia ir normal
	*globalFGColor = currentFG;
	
	//buffer seteado
	for(int i=0; option.texto[i]!=0; i++){
		drawLetterFromChar(option.texto[i]);
	}
	
	//dejo el buffer al ppio del primer recuadro, a la izquierda
	*globalXPos -= (borderLength + borderThickness + gap);
	*globalYPos += (gap + borderThickness);
}

void drawOptionMenuArray(OptionMenu * optionMenu){
	
	setXBuffer(50);
	setYBuffer(50);

	//dibujo todas las opciones
	for(int i=0; i<5; i++){
		drawOption(*(optionMenu->options[i]), getFGColorPointer(), getXBufferPointer(), getYBufferPointer());
        setYBuffer(getYBuffer() + (2*(getSize() * (optionMenu->options[0]->borde.height)))); // globalYPos+= 2*(globalSize * (optionMenu->options[0]->borde.height));
	}
}

void drawMenu(){
	drawPepsiman(500, 0, 5);
	//(18*globalSize*8) + (6*globalSize*2) ->strlen:size*letra*strlen+2*espacio 
	Option registros = {0,1,{4,18, 13}, "SARACATUNGAAAAAAAA"};
	//la primer opcion empieza hovereada
	
	//															13*globalSize +(6*globalSize*2)
	Option hora = {0,0, {4, 13, 13}, "Imprimir Hora"};
	Option snake = {0,0, {4, 11, 13}, "Jugar Snake"};
	Option consola = {0,0, {4, 14, 13}, "Correr Consola"};
	Option restart = {0,0, {4, 14, 13}, "Reiniciar Menu"};
	
	OptionMenu optionMenu ={{&registros, &hora, &snake, &consola, &restart}};

	/*
	modo de uso de consola de comandos:
	-los comandos seran un solo string
	-el espacio se utiliza para introducir el comando (SI LLEGAMOS A NECESITAR ARGUMENTOS HAY QUE HACER AJUSTE)
	*/

	drawOptionMenuArray(&optionMenu);
	while(1){
		char letter = getKbChar();
		switch(letter){
			case '\n':
				if(optionMenu.options[3]->isHovered){	//consola.isHovered
					runConsole(&optionMenu);
					optionMenu.options[3]->isClicked=1;
				}
				else if(optionMenu.options[4]->isHovered){
					drawRectangle(BLACK, 0, 0, getFullWidth(), getFullHeight());
					drawMenu();
				}
				break;
			case 17: case 'w':
				hoverOverPreviousOption(&optionMenu);
				
				break;
			case 20: case 's':
				hoverOverNextoption(&optionMenu);
				break;
			default:
				break;			
		}
	}
}

