#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lists.h"

/*
 * Declaration for my helper function, 
 */

void add_event_helper(Event ** event_ptr, char * name, time_t time);


/*
 * Return a pointer to the struct calendar with name cal_name
 * or NULL if no calendar with this name exists in the cal_list
 */

Calendar *find_calendar(Calendar *cal_list, char *cal_name) {
  
        while(cal_list){ /*if cal_list points to something, the loop will continue to execute */
		
		if (strcmp(cal_list->name, cal_name) == 0){ // compare the strings of the calendar we are looping through
							    // and check to see if that calendar is the one we want	
                     
			return cal_list; // return back a pointer to that calendar 
                }
            
                cal_list = cal_list->next; // iterates through calendar 
                }
        return NULL; //returns NULL if we cant find the calendar in the cal_list
}


/* 
 * Return a pointer to the user with name username or NULL
 *   if no such user exists in user_list 
 */
User *find_user(User *user_list, char *username) {
    	
	while(user_list){ // if user_list points to a user, the loop will continue to iterate
	
		if (strcmp(user_list->name, username) == 0){ // compare the strings of the user we are looping through
							     // and check to see if that user is the one we want 									
	
			return user_list; // return back a pointer to that user
	
		}
	
	user_list = user_list->next; // iterates through users
	}
	
	return NULL; //returns NULL if we cannot find the user in user_list
}


/* 
 * If a calendar with name cal_name does not exist, create a new
 * calendar by this name and insert it at the front of the calendar list.
 * Return values:
 *    0 if successful
 *   -1 if a calendar by cal_name already exists
*/
	
int add_calendar(Calendar **cal_list_ptr, char *cal_name){
       
	 if (find_calendar(*cal_list_ptr, cal_name)){  //calls find_calendar, if calendar is found in the list, return -1
        
		return -1;
        }
        else {  //if calendar is not found in the list, else block will execute

		Calendar * ptr; //make a new pointer to a calendar
		
                if ((ptr = malloc(sizeof(Calendar))) == NULL) { //allocate enough memory for a struct calendar and let the new ptr  
                    perror("malloc");				// point to it, have necessary error checks in case malloc fails
                    exit(1);
                }
					
			
                if ((ptr->name = malloc(sizeof(strlen(cal_name) + 1))) == NULL) { //allocate extra memory for a character array of the length
                    perror("malloc");						// of the name we want to give the calendar, and add an extra space for the '\0' 
                    exit(1);							// also have necessary error checks
                }
					
                strncpy(ptr->name, cal_name, strlen(cal_name)); //copy the string given into the new allocated memory   
		ptr->name[strlen(cal_name)] = '\0'; //set the last character of the new calendar->name string to a null terminator
		                            
                ptr->next = *cal_list_ptr; //set the new calendar obj's next to the head of the cal_list, making the new cal the new head  
                *cal_list_ptr = ptr; // link up the head pointer to point at the new head, which is the new calendar object
		
                return 0; //return 0 for success
                
        }
}
	


/* 
 * Print to stdout a list of all current calendar names (one per line)
*/

void list_calendars(Calendar *cal_list) {
	
	Calendar *ptr; //create a new calendar pointer
	ptr = cal_list; //let new pointer point to head of calendars  
	while(ptr){ //while ptr is still pointing at an object, the loop iterates 
		printf("%s\n", ptr->name); //print out the name of the calendar
		ptr = ptr->next; // iterate through the next calendar
		}

}


/* 
 * If a user with name username does not exist, create a new
 * user by this name and insert it at the end of the user list.
 * Return values:
 *    0 if successful
 *   -1 if username already exists
 */
int add_user(User **user_list_ptr, char *username) {
    
	if (find_user(*user_list_ptr, username)){ //find if there is a user with the same name already
 
                return -1; //return -1 if username already exists

        }

        else {

                User * ptr; //make new user ptr

                if ((ptr = malloc(sizeof(User))) == NULL) { //allocate memory for user, return a ptr to that new allocated memory
                    perror("malloc"); //neseccary error checks if malloc fails
                    exit(1);
                }


                if ((ptr->name = malloc(sizeof(strlen(username) + 1))) == NULL) { //allocates memory for the string
                    perror("malloc"); //error check if malloc fails
                    exit(1);
                }

                strncpy(ptr->name, username, strlen(username)); //copy the string onto the new allocated memory
                ptr->name[strlen(username)] = '\0'; //make last character a null termiator

                ptr->next = *user_list_ptr; // since user can be in any order, the order is the same as calendar
                *user_list_ptr = ptr; //new users become the head of the list

                return 0; //return 0 on success

        }
}



/* 
 * Print to stdout a list of usernames one per line 
 */
void list_users(User *user_list) {

        User *ptr; //make new user ptr
        ptr = user_list; //let new ptr equal to head of user list
        while(ptr){ // while ptr points at User, the loop iterates
                printf("%s\n", ptr->name); //print out the user name
                ptr = ptr->next; //iterates through the next user
                }

}

/*
 * Subscribe the user username to calendar cal_name
 * Return:
 *    0 if successful
 *   -1 if no user exists by this name
 *   -2 if no calendar exists by this name
 *   -3 if this user is already subscribed to this calendar
 */
int subscribe(User *user_list, Calendar *cal_list, char *username, char *cal_name) {
	
	
	User * user;  //makes new user ptr 
	Calendar * cal; //makes new cal ptr
	user = find_user(user_list, username); //let new user ptr point to the user we want to find, null if doesnt exist
	cal = find_calendar(cal_list, cal_name); // let new cal ptr point to calendar we want to find, null if doesnt exist 
	
	if (!user){ // if user doesnt exist, return -1 
		return -1;
		}
	else if (!cal) { // if calendar doesnt exist, return -2
		return -2;
		}
	else { 
		Subscription * sub; //make new sub ptr
		Subscription * index; //make new index ptr
		if (!user->subscriptions)  {  /* user->sub is empty, directly add the new subscription to it */
			if ((sub = malloc(sizeof(Subscription))) == NULL ){ //allocate memory for struct Subscription, return pointer to it 
				perror("malloc"); //error cehck for malloc failure
				exit(1);
			}
			user->subscriptions = sub; // link up user to new subscription 
			user->subscriptions->calendar = cal; //set the new subscription to the calendar the user subscribed to
			return 0; //  return 0 on success
		}
		else { /* the user already has some subscriptions, need to check if user is already subscribed in this statement */  
	 		index = user->subscriptions; //index is a reference pointer
			if (strcmp(index->calendar->name, cal_name) == 0){ //if the user is already subscribed, then return -3 
				return -3;
			}

			while(index->next) { //loop through until the end, since the new subscription needs to be put in the end 
				index = index->next; 
				if (strcmp(index->calendar->name, cal_name) == 0){ //if while looping through, the user is already subscribed, then return -3
					return -3;
					}	 
				}
			if ((sub = malloc(sizeof(Subscription))) == NULL ){ //once at the end, malloc new space for a struct subscription
                                perror("malloc"); //error check
                                exit(1);
                        }
	
			index->next = sub; //set the next of the index to the new subscription
			return 0;//return 0 on success
			}
		}
}


/* 
 *  Return:
 *   0 for success
 *  -1 for calendar does not exist by this name
 */
int add_event(Calendar *cal_list, char *cal_name, char *event_name, time_t time) {
 	
	
	cal_list = find_calendar(cal_list, cal_name); //finds calendar we want

	if (cal_list) { //if calendar exists
		
		add_event_helper(&(cal_list->events), event_name, time); //calls helper function
		
		return 0; //returns 0 on success
		
	}
	else { //if calendar doesn't exist, returns -1
		
		return -1;
	}
}

/* 
 *  Returns void, helper function for add_event
 *  adds a new event based on time to the event_list
 */
void add_event_helper(Event ** event_ptr, char * name, time_t time){

	Event * new_ptr; //make new event ptr	
        if ((new_ptr = malloc(sizeof(Event))) == NULL) { //allocate memory for new struct Event, return pointer to it
                perror("malloc"); //error check
                exit(1); //exit 1 for error
               }

		new_ptr->time = time; //set the new ptr->time to the given time

	        if ((new_ptr->description = malloc(sizeof(strlen(name) + 1))) == NULL) { //allocate memory for the description 
                    perror("malloc"); //error check
                    exit(1);
                }
		

                strncpy(new_ptr->description, name, strlen(name)); //copy the new string into the event description
                new_ptr->description[strlen(name)] = '\0'; //put null char at the end of event description
 
		
		while(*event_ptr){  //while event_ptr points to a event 
			Event * index = *event_ptr; //make new event index as ptr reference 
			if (new_ptr->time <= index->time){ //sort the events by earliest date  
				new_ptr->next = index; 
				*event_ptr = new_ptr;
				break; //break out of loop 
			}
			event_ptr = &(*event_ptr)->next; //iterates over each event
		}
	
		*event_ptr = new_ptr; //if there is no event, add the new event to front of list
		               	
         
}

/*
 * returns 0 if calendar exists, and prints out all the events of that 
 * calendar to std out
 * returns -1 if calendar doesnt exist  
 */
int list_events(Calendar *cal_list, char *cal_name) {
    
	if (find_calendar(cal_list, cal_name)){ //if there is the calendar  
		cal_list = find_calendar(cal_list, cal_name); //set cal pointer to the calendar we want to print the events out of 
		Event * ptr; //make new event ptr
		ptr = cal_list->events; 
		while (ptr){ //while ptr points to event, loop will iterate
			printf("%s\t", ptr->description); //prints out event description for the calendar
			printf("%s\n", ctime(&ptr->time)); //prints out time in readable formate 	 
			ptr = ptr->next; //iterates through events
		}
		return 0;	//return on success
	}
else{
	return -1; //return if calendar doesnt exist
}
}



/* 
 * Print to stdout, the description and time of the next event for 
 * user user_name
 *  Return:
 *   0 on success
 *   -1 if this user_name does not exist or has no events
 */
int print_next_event(Calendar *cal_list, User * user_list, char *user_name) {
return 0;



	Event * Fevent; //make new event reference ptr which holds the address of FIRST event 
	User * userptr; //make new user reference ptr
	Subscription * subptr; //make new subscription refernce ptr
	
	userptr = find_user(user_list, user_name); //pointer of the user which we want to print out the first event
		
	if (userptr){ //if user exists
		
		subptr = userptr->subscriptions;
		if (!subptr){ //if user has no calendar, hence no events, print -1
			return -1;
			}
		else {
			while(subptr){ //for each user subscription check...  
				if (subptr->calendar){ //if user subscription has a calendar
					if (subptr->calendar->events){
						if (Fevent){ //if a first event is already in place
							if (Fevent->time < subptr->calendar->events->time){ //compare old Fevent with current event
								Fevent = subptr->calendar->events; // take the event with the earlier time
							}
						}
						else { 
							Fevent = subptr->calendar->events; //if there is no first event, make the current event the first event
						}
					}					
				}	
				else{
					subptr = subptr->next; //traverse through subscriptions
				}
			}
		}
	}
	else {
		return -1; //return -1 on failure
	}	

	if (Fevent) { //if calendar has events, meaning if first event is not NULL
		printf("%s \t %s", Fevent->description, ctime(&Fevent->time)); //print out event
		return 0; //return 0 on success
		}
	else {
		return -1; //return -1 on failure
		}
	}


/* 
 * Print to stdout a time-ordered list of all events in any calendars
 *  subscribed to by this user 
 *
 *  Do not change the calendar data-structure. 
 *  Return -1 if this user doesn't exist.
 */
int print_all_events(Calendar *cal_list, User * user_list, char *user_name) {
    return 0;
}

