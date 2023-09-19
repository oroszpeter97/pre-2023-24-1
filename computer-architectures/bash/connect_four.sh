#!/bin/bash

#TODO: AI, DIAGONAL CHECK

#Name: Connect Four
#Description:   Connect Four is a two-player connection board game, in which the players choose a color and then take turns dropping
#               colored discs into a seven-column, six-row vertically suspended grid. The pieces fall straight down, occupying the lowest available
#               space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs.
#               Connect Four is a solved game. The first player can always win by playing the right moves.



#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾VARIABLE DECLARATION‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
declare -A Board
declare -A Real_Board
board_width=32
board_height=25
real_board_width=7
real_board_height=6
bot_player=1
#_______________________________________________________________________________________________________



#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾FUNCTION DECLARATION‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
function Menu_Init {
    #ERROR HANDLING FROM FIRST ARGUMENT
    echo `clear`
    if [[ -z "$1" ]]
    then
        printf "Error: -\n\n"
    else
        printf "Error: $1\n\n"
    fi
    
    #DISPLAY OPTIONS
    printf "1. Play\n"
    printf "2. Options\n"
    printf "3. Help\n"
    printf "4. Quit\n\n"
    printf ">"

    #READ USER INPUT THEN FORWARD THEM
    read -n 1 user_input

    case $user_input in

        "1")
            Menu_Play_Init
            ;;

        "2")
            Menu_Options_Init
            ;;

        "3")
            Menu_Help_Init
            ;;

        "4")
            Menu_Quit_Init
            ;;

        *)
            Menu_Init "Wrong Input!"
            ;;
    esac

}

function Menu_Play_Init {
    Board_Init
    Board_Display
    Game
}

function Menu_Options_Init {
    #ERROR HANDLING FROM FIRST ARGUMENT
    echo `clear`
    if [[ -z "$1" ]]
    then
        printf "Error: -\n\n"
    else
        printf "Error: $1\n\n"
    fi

    #DISPLAY CURRENT BOT SETTING
    if [ $bot_player -eq "1" ]
    then
        printf "Bot Player\n\n"
    else
        printf "Human Player\n\n"
    fi
    printf "Change Player? (y/n)\n>"

    #READ USER INPUT AND CHANGE BOT SETTING IF APPLICABLE
    read -n 1 user_input

    case $user_input in

        "y")
            if [ $bot_player -eq "1" ]
            then
                bot_player=0
            else
                bot_player=1
            fi
            Menu_Init
            ;;

        "n")
            Menu_Init
            ;;

        *)
            Menu_Options_Init "Wrong Input!"
            ;;
    esac
}

#DESCRIPTION OF GAME AND HOW TO PLAY
function Menu_Help_Init {
    echo `clear`
    echo "Connect Four is a two-player connection board game, in which the players choose a color and then take turns dropping colored discs into a seven-column, six-row vertically suspended grid. The pieces fall straight down, occupying the lowest available space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs. Connect Four is a solved game. The first player can always win by playing the right moves. To place your piece just press the number of the column you with to place it in."
    read -n 1 asd
    Menu_Init
}

#GAME TERMINATION
function Menu_Quit_Init {
    echo `clear`
    if [[ -z "$1" ]]
    then
        printf "Error: -\n\n"
    else
        printf "Error: $1\n\n"
    fi
    printf "Are you sure you want to quit? (n/y)\n>"

    read -n 1 user_input

    case $user_input in

        "y")
            exit
            ;;

        "n")
            Menu_Init
            ;;

        *)
            Menu_Quit_Init "Wrong Input!"
            ;;
    esac
}

function Board_Init {
    #GENERATE REAL BOARD
    for ((i=0;i<real_board_height;i++)) do
        for ((j=0;j<real_board_width;j++)) do
            Real_Board[$i,$j]=0
        done
    done
    

    #GENERATE BASE LAYER OF BOARD
    for ((i=0;i<=board_height;i++)) do
        for ((j=0;j<=board_width;j++)) do
            Board[$i,$j]=" "
        done
    done

    #GENERATE BORDER
    for ((i=0;i<=board_height;i++)) do
        for ((j=0;j<=board_width;j++)) do
            if [ "$j" -eq "0" ] || [ "$j" -eq "1" ] || [ "$j" -eq "2" ] || [ $j -eq $(($board_width-2)) ] || [ $j -eq $(($board_width-1)) ] || [ $j -eq $board_width ] || [ $i -eq $(($board_height-2)) ] || [ $i -eq $(($board_height-1)) ] || [ $i -eq $board_height ]
            then
                Board[$i,$j]="■"
            fi
        done
    done

    #GENERATE VERTICAL SEPERATOR
    for ((i=0;i<=board_height-3;i++)) do
        for ((j=6;j<=board_width-3;j+=4)) do
            Board[$i,$j]="|"
        done
    done

    #GENERATE HORIZONTAL SEPERATOR
    for ((i=3;i<=board_height-3;i+=4)) do
        for ((j=3;j<=board_width-3;j++)) do
            Board[$i,$j]="─"
        done
    done

    #GENERATE INTERSECTION SEPERATOR
    for ((i=3;i<=board_height-3;i+=4)) do
        for ((j=6;j<=board_width-3;j+=4)) do
            Board[$i,$j]="┼"
        done
    done

    local row_number=1
    #GENERATE ROW NUMBERS
    for ((i=1;i<=board_height-3;i+=4)) do
        Board[$i,1]=$row_number
        row_number=$(($row_number+1))
    done

    local column_number=1
    #GENERATE COLUMN NUMBERS
    for ((i=4;i<=board_width-3;i+=4)) do
        Board[24,$i]=$column_number
        column_number=$(($column_number+1))
    done
}

function Board_Display {
    echo `clear`
    for ((i=0;i<=board_height;i++)) do
        for ((j=0;j<=board_width;j++)) do
            printf "${Board[$i,$j]} "
        done
        printf "\n"
    done
    printf "\n"
}

function Marker_Add_Player1 {
    local row=$(($1-1))
    local column=$(($2-1))

    Board[$(($row-1)),$(($column-1))]="╔"
    Board[$(($row-1)),$(($column))]="═"
    Board[$(($row-1)),$(($column+1))]="╗"
    Board[$(($row)),$(($column+1))]="║"
    Board[$(($row+1)),$(($column+1))]="╝"
    Board[$(($row+1)),$(($column))]="═"
    Board[$(($row+1)),$(($column-1))]="╚"
    Board[$(($row)),$(($column-1))]="║"

    Board_Display
}

function Marker_Add_Player2 {
    local row=$(($1-1))
    local column=$(($2-1))

    Board[$(($row-1)),$(($column-1))]="⇖"
    Board[$(($row-1)),$(($column+1))]="⇗"
    Board[$(($row+1)),$(($column+1))]="⇘"
    Board[$(($row+1)),$(($column-1))]="⇙"
    Board[$(($row)),$(($column))]="■"

    Board_Display
}

function Verify_Move_Player_1 {
    local column=$(($1-1))
    local empty_c=0
    local v_row=5

    while [ $empty_c -eq "0" ] && [ $v_row -ge 0 ]
    do
        if [ "${Real_Board[$v_row,$column]}" -eq "0" ]
        then
            empty_c=1
            Real_Board[$v_row,$column]=1
        fi
        v_row=$(($v_row-1))
    done

    if [ $empty_c -eq "1" ]
    then
        Marker_Add_Player1 $((2+($v_row+1)*4)) $((5+$column*4))
    else
        Player_1_Move_Input "Column is already full!"
    fi
}

function Verify_Move_Player_2 {
    local column=$(($1-1))
    local empty_c=0
    local v_row=5

    while [ $empty_c -eq "0" ] && [ $v_row -ge 0 ]
    do
        if [ "${Real_Board[$v_row,$column]}" -eq "0" ]
        then
            empty_c=1
            Real_Board[$v_row,$column]=2
        fi
        v_row=$(($v_row-1))
    done

    if [ $empty_c -eq "1" ]
    then
        Marker_Add_Player2 $((2+($v_row+1)*4)) $((5+$column*4))
    else
        Player_2_Move_Input "Column is already full!"
    fi
}

function Verify_Move_Bot {
    local column=$(($1-1))
    local empty_c=0
    local v_row=5

    while [ $empty_c -eq "0" ] && [ $v_row -ge 0 ]
    do
        if [ "${Real_Board[$v_row,$column]}" -eq "0" ]
        then
            empty_c=1
            Real_Board[$v_row,$column]=2
        fi
        v_row=$(($v_row-1))
    done

    if [ $empty_c -eq "1" ]
    then
        Marker_Add_Player2 $((2+($v_row+1)*4)) $((5+$column*4))
    else
        Bot_Move_Input
    fi
}

function Bot_Move_Input {

    bot_move=$(($RANDOM % 7))

    Verify_Move_Bot $bot_move
}

function Player_1_Move_Input {
    #ERROR HANDLING FROM FIRST ARGUMENT
    echo `clear`
    Board_Display
    if [[ -z "$1" ]]
    then
        printf "Error: -\n\n"
    else
        printf "Error: $1\n\n"
    fi
    
    printf "Player 1 move!\n>"
    read -n 1 user_input

    case $user_input in

        [1-7])
            Verify_Move_Player_1 $user_input
            ;;

        *)
            Player_1_Move_Input "Wrong Input!"
            ;;
    esac
}

function Player_2_Move_Input {
    #ERROR HANDLING FROM FIRST ARGUMENT
    echo `clear`
    Board_Display
    if [[ -z "$1" ]]
    then
        printf "Error: -\n\n"
    else
        printf "Error: $1\n\n"
    fi
    
    printf "Player 2 move!\n>"
    read -n 1 user_input

    case $user_input in

        [1-7])
            Verify_Move_Player_2 $user_input
            ;;

        *)
            Player_2_Move_Input "Wrong Input!"
            ;;
    esac
}

function Check_Win {
    local player_1_win=0
    local player_2_win=0
    #PLAYER 1 HORIZONTAL CHECK
    for ((i=0;i<real_board_height;i++)) do
        local counter=0
        for ((j=0;j<real_board_width;j++)) do
            if [ "${Real_Board[$i,$j]}" -eq "1" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_1_win=1
                fi
            else
                counter=0
            fi
        done 
    done
    #PLAYER 1 VERTICAL CHECK
    for ((i=0;i<real_board_width;i++)) do
        local counter=0
        for ((j=0;j<real_board_height;j++)) do
            if [ "${Real_Board[$j,$i]}" -eq "1" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_1_win=1
                fi
            else
                counter=0
            fi
            
        done
    done
    #PLAYER 1 DIAGONAL RIGHT CHECK

    #TOP HALF
    for ((i=3;i<6;i++)) do
        y=$i
        x=0
        counter=0
        while [ "$y" -ge "0" ] 
        do
            if [ "${Real_Board[$y,$x]}" -eq "1" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_1_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y-1))
            x=$(($x+1))
        done
    done

    #BOTTOM HALF
    for ((i=0;i<3;i++)) do
        y=$i
        x=6
        counter=0
        while [ "$y" -le "5" ]
        do
            if [ "${Real_Board[$y,$x]}" -eq "1" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_1_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y+1))
            x=$(($x-1))
        done
    done

    #PLAYER 1 DIAGONAL LEFT CHECK

    #TOP HALF
    for ((i=0;i<3;i++)) do
        y=$i
        x=0
        counter=0
        while [ "$y" -le "5" ]
        do
            if [ "${Real_Board[$y,$x]}" -eq "1" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_1_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y+1))
            x=$(($x+1))
        done
    done

    #BOTTOM HALF
    for ((i=5;i>3;i--)) do
        y=$i
        x=6
        counter=0
        while [ "$y" -ge "0" ] 
        do
            if [ "${Real_Board[$y,$x]}" -eq "1" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_1_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y-1))
            x=$(($x-1))
        done
    done

    #PLAYER 2 HORIZONTAL CHECK
    for ((i=0;i<real_board_height;i++)) do
        local counter=0
        for ((j=0;j<real_board_width;j++)) do
            if [ "${Real_Board[$i,$j]}" -eq "2" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_2_win=1
                fi
            else
                counter=0
            fi
        done 
    done
    #PLAYER 2 VERTICAL CHECK
    for ((i=0;i<real_board_width;i++)) do
        local counter=0
        for ((j=0;j<real_board_height;j++)) do
            if [ "${Real_Board[$j,$i]}" -eq "2" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_2_win=1
                fi
            else
                counter=0
            fi
            
        done
    done
    #PLAYER 2 DIAGONAL RIGHT CHECK

     #TOP HALF
    for ((i=3;i<6;i++)) do
        y=$i
        x=0
        counter=0
        while [ "$y" -ge "0" ] 
        do
            if [ "${Real_Board[$y,$x]}" -eq "2" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_2_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y-1))
            x=$(($x+1))
        done
    done

    #BOTTOM HALF
    for ((i=0;i<3;i++)) do
        y=$i
        x=6
        counter=0
        while [ "$y" -le "5" ]
        do
            if [ "${Real_Board[$y,$x]}" -eq "2" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_2_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y+1))
            x=$(($x-1))
        done
    done

    #PLAYER 2 DIAGONAL LEFT CHECK

    #TOP HALF
    for ((i=0;i<3;i++)) do
        y=$i
        x=0
        counter=0
        while [ "$y" -le "5" ]
        do
            if [ "${Real_Board[$y,$x]}" -eq "2" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_2_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y+1))
            x=$(($x+1))
        done
    done

    #BOTTOM HALF
    for ((i=5;i>3;i--)) do
        y=$i
        x=6
        counter=0
        while [ "$y" -ge "0" ] 
        do
            if [ "${Real_Board[$y,$x]}" -eq "2" ]
            then
                counter=$(($counter+1))
                if [ "$counter" -ge "4" ]
                then
                    player_2_win=1
                fi
            else
                counter=0
            fi
            
            y=$(($y-1))
            x=$(($x-1))
        done
    done



    if [ "$player_1_win" -eq "1" ]
    then
        Winning_Screen "PLAYER 1 WINS"
    fi
    if [ "$player_2_win" -eq "1" ]
    then
        Winning_Screen "PLAYER 2 WINS"
    fi
}

function Check_Possible_Move {
    board_is_full=1
    for ((i=0;i<real_board_height;i++)) do
        for ((j=0;j<real_board_width;j++)) do
            if [ "${Real_Board[$i,$j]}" -eq "0" ]
            then board_is_full=0
            fi
        done
    done
    if [ "$board_is_full" -eq 1 ]
    then 
        Winning_Screen "DRAW"
    fi
}

function Winning_Screen {
    echo `clear`
    printf "$1"
    read -n 1 asd
    Menu_Init
}

function Game {
    while :
    do
        if [ "$bot_player" -eq "1" ]
        then
            Player_1_Move_Input
            Check_Win
            Check_Possible_Move
            Bot_Move_Input
            Check_Win
            Check_Possible_Move
        else
            Player_1_Move_Input
            Check_Win
            Check_Possible_Move
            Player_2_Move_Input
            Check_Win
            Check_Possible_Move
        fi
        
    done
    
}


#_______________________________________________________________________________________________________


#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾HELP‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
#ERROR HANDLING FROM FIRST ARGUMENT
echo `clear`
if [[ -z "$1" ]]
    then
        printf ""
    else
        if [[ $1 == "-h" ]]
        then
            echo `clear`
            echo "Connect Four is a two-player connection board game, in which the players choose a color and then take turns dropping colored discs into a seven-column, six-row vertically suspended grid. The pieces fall straight down, occupying the lowest available space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs. Connect Four is a solved game. The first player can always win by playing the right moves. To place your piece just press the number of the column you with to place it in."
            read asd
            exit    
        else 
            echo `clear`
            echo "$1 is not a recognised flag!"
            read asd
            exit
        fi
    fi
#_______________________________________________________________________________________________________


#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾GAME LOOP‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
while :
do
    Menu_Init
done
#_______________________________________________________________________________________________________