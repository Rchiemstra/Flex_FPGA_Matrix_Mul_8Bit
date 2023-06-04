#include "address_map_arm.h"

//this enum are for the button menu selection
enum move
{
    horizontal,
    vertical,
    rotate
};

//this enum is for keeping track of the half on which the index is ATM
enum lo
{
    top,
    bot
};

//simple positional x,y struct
struct pos
{
    int x;
    int y;
};


//These variables are for handeling rotation order, depending on position of the index either the top or bot rotation is used
int ro_top[4] = {0, 1, 6, 5};
struct pos bro_top[4] = {{.x = 1, .y = 0}, {.x = 2, .y = 1}, {.x = 1, .y = 1}, {.x = 0, .y = 1}};

int ro_bot[4] = {6, 2, 3, 4};
struct pos bro_bot[4] = {{.x = 1, .y = 1}, {.x = 2, .y = 1}, {.x = 2, .y = 2}, {.x = 1, .y = 2}};

//This matrix index the position of hex positions in a matrix
int moves[3][3] = {{0, 0, 0},
                   {5, 6, 1},
                   {4, 3, 2}};

//This is used to convert between the matrix and an index variable.
struct pos matrix[7] = {{.x = 1, .y = 0}, {.x = 2, .y = 1}, {.x = 2, .y = 2}, {.x = 1, .y = 2}, {.x = 0, .y = 2}, {.x = 0, .y = 1}, {.x = 1, .y = 1}};

enum lo location = top;


//This function is meant for rotating the top half of the hex display
//the current position and switch values are passed to the function
//and the next position in rotation is returned 
struct pos find_next_top(struct pos nexus_pos, _Bool SW)
{
    struct pos temp_pos;

    for (int i = 0; i < 4; i++)
    {
        if (ro_top[i] == moves[nexus_pos.x][nexus_pos.y])
        {
            if (i < 3)
            {
                temp_pos.x = bro_top[i + 1].x;
                temp_pos.y = bro_top[i + 1].y;
            }
            else
            {
                temp_pos.x = bro_top[0].x;
                temp_pos.y = bro_top[0].y;
            }
            return temp_pos;
        }
    }
    return temp_pos;
}

//Same as find_next_top but for the bottem
struct pos find_next_bot(struct pos nexus_pos, _Bool SW)
{
    struct pos temp_pos;

    for (int i = 0; i < 4; i++)
    {
        if (ro_bot[i] == moves[nexus_pos.x][nexus_pos.y])
        {
            if (i < 3)
            {
                temp_pos.x = bro_bot[i + 1].x;
                temp_pos.y = bro_bot[i + 1].y;
            }
            else
            {
                temp_pos.x = bro_bot[0].x;
                temp_pos.y = bro_bot[0].y;
            }
            return temp_pos;
        }
    }
    return temp_pos;
}

//move_index is used to handle the inputs given
//as parameters it is passed the current index which is the position of de indicated LED strip in a 32bit variable,
//mov, which is the selected type of operation for the index
//and finally the switch value is passed to determine the direction of the operation
int move_index(int index, enum move mov, _Bool SW)
{
    //new_index is the position of the LED independent of the current display in which it finds itself
    struct pos temp_pos, nexus_pos;
    int move_hex = 0;
    int new_index = index % 8;

    //A position inside the matrix is determined based on the new_index which was just created.
    //2 are made so the default value can be referenced for later uses
    temp_pos.x = matrix[new_index].x;
    temp_pos.y = matrix[new_index].y;
    nexus_pos.x = matrix[new_index].x;
    nexus_pos.y = matrix[new_index].y;

    //switch through the mov operations
    switch (mov)
    {
    case horizontal:
    {
        //if the current position is in the middle of the matrix, a horizontal movement
        //will always result in switching of the hex display. 
        //move_hex is a variable which keeps track of this movement
        if (temp_pos.x == 1){
            if (SW){
                move_hex++;
            }else{
                move_hex--;
            }
            break;
        }

        //for horizontal movement on de outside LED's of the displays, first switching between the internal sides needs to occur
        //if it already finds itself on the outside of its movement, the sides need to be switched and move_hex adjusted
        //to switch between displays
        else{
            if (SW){
                if (temp_pos.x == 2){
                    temp_pos.x = 0;
                    move_hex--;
                }else{
                    temp_pos.x = 2;
                }
                break;
            }else{
                if (temp_pos.x == 0){
                    temp_pos.x = 2;
                    move_hex++;
                }else{
                    temp_pos.x = 0;
                }
                break;
            }
        }
        break;
    }

    case vertical:
    {   
        //switching verticaly when the LED's position is in the middel section of the matrix,
        //means swiching between the 3 layers in the switch selected direction
        //when the end of either side is reached and a next step in the same direction would exceed the ending
        //the position is switched to that of the opposite end.
        if (nexus_pos.x == 1){
            if (SW){
                if (temp_pos.y == 0){
                    temp_pos.y = 2;
                }else{
                    temp_pos.y--;
                }
            }else{
                if (temp_pos.y == 2){
                    temp_pos.y = 0;
                }else{
                    temp_pos.y++;
                }
            }
            break;
        }
        //switching on the edge is just switching between the 2 LED's
        else if (nexus_pos.x == 0 || nexus_pos.x == 2){
            if (SW){
                if (nexus_pos.y == 1){
                    temp_pos.y = 2;
                }else{
                    nexus_pos.y = 1;
                }
            }else{
                if (nexus_pos.y == 2){
                    temp_pos.y = 1;
                }else{
                    temp_pos.y = 2;
                }
            }
        }
        break;
    }
    
    
    //rotation is currently kinda skuffed and only works on some locations, not all due to time conflict
    case rotate:
    {
        //at the top of handeling the rotation of the LED, first is determine if it is relevant to switch the current half
        //on which the LED resides
        if (moves[temp_pos.x][temp_pos.y] == 2 || moves[temp_pos.x][temp_pos.y] == 4)
        {
            location = bot;
        }
        if (moves[temp_pos.x][temp_pos.y] == 5 || moves[temp_pos.x][temp_pos.y] == 1)
        {
            location = top;
        }


        //rotation is handled based on the current position an switch position.
        //the switch cases inside rotation are used to determine which have needs to be used for rotating.
        // after that find_next_bot or find_next_top are used to change the position
        if (SW)
        {
            switch (moves[temp_pos.x][temp_pos.y])
            {
            case 2:
            case 3:
            case 4:
                temp_pos = find_next_bot(temp_pos, SW);
                break;

            case 0:
            case 1:
            case 5:
                temp_pos = find_next_top(temp_pos, SW);
                break;

            case 6:
                if (location == top)
                {
                    temp_pos = find_next_top(temp_pos, SW);
                }
                if (location == bot)
                {
                    temp_pos = find_next_bot(temp_pos, SW);
                }
                break;
            }
        }
        else
        {
            switch (moves[temp_pos.x][temp_pos.y])
            {
            case 2:
            case 3:
            case 4:
                temp_pos = find_next_bot(temp_pos, SW);
                break;

            case 0:
            case 1:
            case 5:
                temp_pos = find_next_top(temp_pos, SW);
                break;

            case 6:
                if (location == top)
                {
                    temp_pos = find_next_top(temp_pos, SW);
                }
                if (location == bot)
                {
                    temp_pos = find_next_bot(temp_pos, SW);
                }
                break;
            }
        }
    }
    }

    //this is where the moving between displays is handled
    //it determines the direction in which the index needs to be adjusted
    //based on the either negative or positive value of move_hex
    //it also handles overflow from the first to last, or last to first display
    if (move_hex != 0)
    {
        if (move_hex > 0)
        {
            if ((index + 8) > 31)
            {
                index += (8 - 32);
            }
            else
            {
                index += 8;
            }
        }
        if (move_hex < 0)
        {
            if ((index - 8) < 0)
            {
                index += (-8 + 32);
            }
            else
            {
                index -= 8;
            }
        }
    }

    //index is adjusted based on the new position
    //this is done by using the difference between the new and old value  
    index = index - moves[nexus_pos.y][nexus_pos.x] + moves[temp_pos.y][temp_pos.x];

    return index;
}

//a function to write a 1 to a position based on the index provided
long int write_hex(int index, long int HEX)
{
    return (HEX | (1 << index));
}

//a function to write a 0 to a position based on the index provided
long int remove_hex(int index, long int HEX)
{
    return (HEX & ~(1 << index));
}

int main(void)
{
    //addresses of all used parts of the FPGA
    volatile int *LED_ptr = (int *)LED_BASE;      
    volatile int *LEDR_ptr = (int *)LEDR_BASE;    
    volatile int *SW_switch_ptr = (int *)SW_BASE; 
    volatile int *KEY_ptr = (int *)KEY_BASE;      
    volatile int *HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE;

    //setting default values for some variables
    long int HEX_bits = 0x00000000;
    long int LED_bits = 0x00000000;
    long int WRITE_OUT = 0x00000000;

    int SW_value, KEY_value, index = 0;

    volatile int delay_count; 

    while (1)
    {
        //resetting the neccesery values
        LED_bits = 0x00000000;
        WRITE_OUT = 0x00000000;

        //reading the current values of the KEYS and SWITCHES
        SW_value = *(SW_switch_ptr); 
        KEY_value = *(KEY_ptr);      

        //switching based on which KEY is pressed
        switch (KEY_value)
        {
        //this is for the horizontal button
        case 0x1:
            if (SW_value & 0x1)
            {
                index = move_index(index, horizontal, 1);
            }
            else
            {
                index = move_index(index, horizontal, 0);
            }
            break;
        //this is for the vertical button
        case 0x2:
            if (SW_value & 0x2)
            {
                index = move_index(index, vertical, 1);
            }
            else
            {
                index = move_index(index, vertical, 0);
            }
            break;
        //this is for the rotation button
        case 0x4:
            if (SW_value & 0x4)
            {
                index = move_index(index, rotate, 1);
            }
            else
            {
                index = move_index(index, rotate, 0);
            }
            break;

        //the last butten is for handeling the writing or removing of a bit in HEX_bits
        case 0x8:
            if (SW_value & 0x8)
            {
                HEX_bits = remove_hex(index, HEX_bits);
            }
            else
            {
                HEX_bits = write_hex(index, HEX_bits);
            }
            break;

        default:
            break;
        }

        //WRITE_OUT is the combination of the current index and HEX_bits
        WRITE_OUT = (HEX_bits | ((1 << index) & 0xffffffff));
        *(HEX3_HEX0_ptr) = WRITE_OUT;
        //the value is also written to the bottem LED's so the current index is easier to determine
        //mostly for debugging purposes
        *(LED_ptr) = (index & 0xffffffff);

        //wait for as long as the key continues to be pressed
        //so no actions are repeated on a single button press
        while (*KEY_ptr);

        //delay
        for (delay_count = 350000; delay_count != 0; --delay_count); 
    }
}