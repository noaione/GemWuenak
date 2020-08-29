#include <stdio.h> 
#include<cstdlib> 
#include<ctime> 
#include<conio.h> 



enum Ball_Direction{STOP, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT};



class Ball{ //Ball movements
	public:
		int x, y, center_x, center_y; 
		Ball_Direction direction; 
		
		
		
		Ball(int x, int y){ 
			this->center_x = x; 
			this->center_y = y;
			this->x = x; 
			this->y = y;
			this->direction = STOP; 
		}
		
		
		void reset_ball(){
			x = center_x;
			y = center_y;
			direction = STOP; 
		}
		
		
		void change_ball_direction(Ball_Direction d){
			direction = d;
		}
		
		
		void randomize_ball_direction(){
			direction = (Ball_Direction)((rand()%6) + 1);
		}
		
		
		void move_ball(){ 
			switch(direction){
				case STOP:
					break;
				case LEFT:
					x--;
					break;
				case RIGHT:
					x++;
					break;
				case UPLEFT:
					x--;
					y--;
					break;
				case DOWNLEFT:
					x--;
					y++;
					break;
				case UPRIGHT:
					x++;
					y--;
					break;
				case DOWNRIGHT:
					x++;
					y++;
					break;
				default: 
					break;
			}
		}		
}; 



class Blade{ //Blade var
	public:
		int x, y, initial_x, initial_y; 
	
		
		Blade(int x, int y){
			this->initial_x = x;
			this->initial_y=y;
			this->x = x;
			this->y = y;				
		}
		
		
		void blade_reset(){
			x = initial_x;
			y = initial_y;
		}
		
		
		void blade_move_up(){
			y--;
		}
		
		
		void blade_move_down(){
			y++;
		}
}; 




class Ping_Pong{ //Main var
	public:
		int width, height, score_1, score_2;	
		char up_1, down_1, up_2, down_2; 
		bool terminate; 
		
		Ball *ball; 
		Blade *player_1, *player_2;
		Ping_Pong(int width, int height){
			srand(time(NULL));
			
			
			this->terminate = false;
			this->up_1 = 'q'; 
			this->up_2 = 'p'; 
			this->down_1 = 'a'; 
			this->down_2 = 'l'; 
			this->score_1 = 0; 
			this->score_2 = 0;
			
			this->width=width; 
			this->height = height;
			
			this->ball = new Ball(width/2, height/2);
			this->player_1 = new Blade(1, height/2 -3);
			this->player_2 = new Blade(width-2, height/2 -3);
		}
		
		
		void increment_score(Blade *player){ //Scoring System
			if (player == player_1) score_1+=5; 
			else score_2+=5;
			
			if(player >= 25){
				puts("");
				puts("");
				if (player == player_1) puts("PLAYER 1 WINS!!"); 
				else puts("PLAYER 2 WINS!!"); 
			}else{
				ball->reset_ball(); 
				player_1->blade_reset(); 
				player_2->blade_reset();
			}
			
		}
		
		
		void draw_layout(){ //Layout
			system("cls");
			
			for (int i=0; i< width+2; i++) printf("\xB2");
			printf("\n");
			
			
			for(int i=0; i<height; i++){ 
				for(int j=0; j<width; j++){
					
					if (j==0) printf("\xB2");
					
					if(ball->x == j && ball->y == i) printf("O");
																
					
					else if(player_1->x == j && player_1->y == i) printf("\xDB");
					else if(player_1->x == j && player_1->y + 1 == i) printf("\xDB");
					else if(player_1->x == j && player_1->y + 2 == i) printf("\xDB");
					else if(player_1->x == j && player_1->y + 3 == i) printf("\xDB");
					
					
					else if(player_2->x == j && player_2->y == i) printf("\xDB");
					else if(player_2->x == j && player_2->y + 1 == i) printf("\xDB");
					else if(player_2->x == j && player_2->y + 2 == i) printf("\xDB");
					else if(player_2->x == j && player_2->y + 3 == i) printf("\xDB");
					
					
					else printf(" "); 
					
					if (j==width-1) printf("\xDB");
				} 
				
				
                printf("\xB2");
                puts("");
			} 
			
			
			for (int i=0; i< width+2; i++) printf("\xDB");
			printf(" ");
			
			
			printf("Score_P1: %d",score_1);
			printf("\t\t\tScore_P2: %d",score_2);
			puts("");
			
		} 
		
		
		void play(){ //Gameplay
			ball->move_ball(); 
			
			if (_kbhit()){ 
				char key = _getch();
				
				
				if (key == up_1 && player_1->y > 0) player_1->blade_move_up();		
				else if (key == up_2 && player_2->y > 0) player_2->blade_move_up();
				else if (key == down_1 && player_1->y + 4 < height) player_1->blade_move_down();
				else if (key == down_2 && player_2->y + 4 < height) player_2->blade_move_down();
				else if (key == 't') terminate = true;				
				if (ball->direction == STOP) ball->randomize_ball_direction();
			}
		}
		
		void monitor_ball(){ //Bouncing the blade
			
			
			for (int i =0; i<4; i++)
				if(ball->x == player_1->x + 1)
					if (ball->y == player_1->y + i)
						ball->change_ball_direction( (Ball_Direction)(rand()%3 + 4 ));
			
			
			for (int i =0; i<4; i++)
				if(ball->x == player_2->x - 1)
					if (ball->y == player_2->y + i)
						ball->change_ball_direction( (Ball_Direction)(rand()%3 + 1 ));
			
			
			if (ball->y == height-1)
				ball->change_ball_direction(ball->direction == DOWNRIGHT ? UPRIGHT : UPLEFT);
			
			
			if (ball->y == 0)
				ball->change_ball_direction(ball->direction == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
			
			
			if(ball->x == width-1)
				increment_score(player_1);
			
			
			if(ball->x == 0)
				increment_score(player_2);
				
		}
		
		
		void lets_ping_pong(){
			while(!terminate){
				draw_layout();
				play();
				monitor_ball();
			}
		}
};



int ping_pong_game(int sw = 40, int sy = 20){
	hideCursor();
	Ping_Pong game(sw, sy); 
	game.lets_ping_pong();
	return 0; 
}

