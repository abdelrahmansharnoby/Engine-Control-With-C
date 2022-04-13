/*
 ============================================================================
 Name        : projectc.c
 Author      : Sharnoby
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1
enum Status{
	ON = 1 ,OFF=0
};
struct vehicle{ // structure for the vehicle contain all the vehicle data
	int speed  ;
	char traffic;
	int room_temprature;
	int engine_temprature;
	enum Status AC;
	enum Status Engine_control;
	enum Status vehicle_status;
} vehicle_default = {100,'G',20,125,OFF,OFF,OFF};
typedef struct vehicle vehicle;
int init();
char engine_on(vehicle *v); // function for the engine to turn on
void set_trafiic(vehicle *v); // function to set the traffic light
void set_roomTemp(vehicle *v); // function to set the room temprature
void set_engineTemp(vehicle *v); // function that give the sensor read for the engine
void status_checkt(vehicle *v); // fuction to check the the temprature to handle the casses of the temprature
void set_speed(vehicle *v,int speed);
void check_roomtemp(vehicle *v); // function to check the engine temprature to handle the cases of the room temprature
void check_engineT(vehicle * v); //function to check the engine temprature to handle the cases of the room temprature
int main(void) { // main function calling the init in while 1 to make the program run continously
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	vehicle v1 = vehicle_default;

	while(1){  // while 1 to make the program run continously
		if(init(&v1)== 0){
			return 0;
		}

	}
	return 0;
}

int init(vehicle * v){ // the init function that handle the inputs from the user

	char state;
	printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n"); // the main menu
	scanf(" %c",&state); // input the choice that the user enters
	switch(state){ // switch case to handle the choice
	case 'a':
	case 'A':
		while(1){
			if(engine_on(v)=='a'){ //if user presses a turn on engine
				break;
			}
		}
		break;
	case 'b': // if the user presses b turn off the vehicle
	case 'B':
		printf("vehicle turned off\n");
		break;
	case 'c':
	case 'C': // if the user presses c the program quit
		return 0;
		break;
	default: // to handle the case if any other input is pressed
		printf("please enter a valid input\n");




	}

}
char engine_on(vehicle * v){ // function to turn on the vehicle
	char s;
	printf("Engine ON\n");
	v->vehicle_status=ON;
	// this print to show the status of the engine
	printf("Engine Status:%s\nEngine Temperature:%d\nEngine Temperature Control:%s\nVehicle Speed:%d\nRoom Temperature:%d\nAC status:%s\nTraffic Light:%c\n",
			v->vehicle_status==1? "ON":"OFF",
					v->engine_temprature,
					v->Engine_control==1? "ON":"OFF",
							v->speed,
							v->room_temprature,
							v->AC==1? "ON":"OFF",
									v->traffic);
	// print to handle the user input
	printf("a. Turn off the engine\nb. Set the traffic light color.\nc. Set the room temperature (Temperature Sensor)\nd. Set the engine temperature\n");
	scanf(" %c",&s);
	if(s=='a'){ // when a is pressed the engine goes off
		return 'a';
	}
	else if(s=='b'){ // when b is pressed the traffic is set
		set_trafiic(v);
	}
	else if(s=='c'){ // when c is pressed set the room temprature
		set_roomTemp(v);
	}
	else if(s== 'd'){ // when d is pressed set the engine temprature
		set_engineTemp(v);
	}
	else{
		printf("please enter a valid input");
	}
	return 0;
}
void set_trafiic(vehicle *v){
	char traffic; // input taken from the user to do a function from the menu of the engine
	scanf(" %c",&traffic);
	v->traffic=traffic; // set the traffic in the struct vehicle of the car
	printf("traffic is set\n");
	status_checkt(v); // function that handle the cases of the of the traffic

}
void set_roomTemp(vehicle *v){
	int roomTemp;    // input taken the room temprate from the user
	scanf(" %d",&roomTemp); // take input
	v->room_temprature= roomTemp; //set the value of the temprature in the struct
	printf("room temprature is set\n");
	check_roomtemp(v); // function check to handle the cases of the room temprature
}
void set_engineTemp(vehicle *v){ // function to set the engine temprature
#if WITH_ENGINE_TEMP_CONTROLLER
	int engine_temp;
	scanf(" %d",&engine_temp); // input taken from the user the engine temprature
	v->engine_temprature = engine_temp; // changing the room engine temprature in the struct
	check_engineT(v); // function to handle the cases of the engine temprature
# endif
}
void status_checkt(vehicle *v){ // function to handle the traffic if Green set speed to 100
	switch(v->traffic){
	case'G' :
		if(v->speed==100){
			break;
		}
		else{
			set_speed(v,100);
			printf("speed changed\n");
			break;
		}
	case 'R': // if red set the speed to 0
		if(v->speed==0){
			break;
		}
		else{
			set_speed(v,0);
			printf("speed changed\n");
			break;
		}
	case 'O': // if yellow set the speed to 30
		if(v->speed == 30){
			if(v->AC==OFF){ // if the speed is 30 do the following
						            v->AC=ON; // turn on the AC
						            printf("AC ON\n");
						            v->room_temprature*=(5.00/4.00); // change the temprature
						            v->room_temprature++;
						            printf("room temprature changed\n");
						            v->Engine_control=ON; // open the controller
						            printf("control is on");
						            v->engine_temprature*=(5.00/4.00);
						            v->engine_temprature++;
						            printf("engine temprature changed\n");
			}
			break;
		}
		else{
			set_speed(v,30);
			printf("speed changed\n");
			if(v->speed==30){
			        if(v->AC==OFF){
			            v->AC=ON;
			            printf("AC ON\n");
			            v->room_temprature*=(5.00/4.00);
			            v->room_temprature++;
			            printf("room temprature changed\n");
			            v->Engine_control=ON;
			            printf("control is on");
			            v->engine_temprature*=(5.00/4.00);
			            v->engine_temprature++;
			            printf("engine temprature changed\n");
			        }
			    }
			break;
		}
	default:
		printf("please enter a valid input");
	}

}
void set_speed(vehicle *v,int speed){ // function to set the speed
	v->speed= speed;
}
void check_roomtemp(vehicle *v){ // function to handle the change in the room temprature
	if(v->room_temprature<=10){ // if room temprature < 10
		v->AC= ON; // turn on the AC
		printf("AC activated");
		v->room_temprature=20;  // change room temprature to 20
	}
	else if(v->room_temprature>=30){ // if the room temprature > 30
		v->AC= ON; // turn on the AC
		printf("AC activated");
		v->room_temprature=20; // make the room tempratue 20
	}
	else{
		if(v->AC== ON){ // the the temprature is between 20 and 30 if the AC is on turn it off
			v->AC=OFF;
			printf("AC Di-Activated");
		}
	}
}
void check_engineT(vehicle *v){  // function to check the engine temprature and handle it
	if(v->engine_temprature<100){ // if the engine tempratue is less then 100
		v->Engine_control=ON; // turn on the engine control
		printf("controller is on");
		v->engine_temprature=100; // and set the engine control to 100
	}
	else if(v->engine_temprature>150){  // if the engine control is higher than 150
		v->Engine_control=ON; // turn on the engine control
		printf("controller is on");
		v->engine_temprature=100; // set the engine temprature to 100
	}
	else{
		if(v->Engine_control== ON){ // if the engine tempratue is between 100 and 150 if the engine control is on turn it off
			v->Engine_control=OFF;
			printf("controller Di-Activated\n");
		}
	}
} // the END :)
