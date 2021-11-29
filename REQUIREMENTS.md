# :robot: Project requirements 
Snake game using Arduino UNO and 8x8 led matrix

## ```PHASE 1:``` Menu design and proof of concept
Deadline: ```December 8th, 23:59```
 
In this phase you will choose the
game (confirm it with me), implement the menu (par the requirements),
create the github repo (yes, a separate one) and implement the proof of
concept of the game (aka first level).
      
## ```PHASE 2:``` Progress update
Deadline: ```16th of December``` (lab presentation)

Here you will present the progress update in the following
week. You will ```be graded``` on your progress update as well, not
only on final result.

## ```PHASE 3:``` Finishing touches
Deadline: ```anywhere in the week of 20th-24th of December ```

Basically, finishing the game (and maybe the build
around it) and presenting it in the last week before Christmas. This
includes both github and the physical presentation.


# :thought_balloon: Menu requirements 

```PHASE 1```

```Menu Task:``` Create a menu for your game, emphasis on the game. You
should scroll on the LCD with the ```joystick```. Remember you have quite a
lot of flexibility here, but do not confuse that with a free ticket to slack
off. 

The menu should include the following functionality:
1. When powering up a game, a greeting message should be shown for a few moments.
2. Should contain roughly the following categories:
    * Start game, starts the initial level of your game
    * Highscore:
      - Initially, we have 0.
      - Update it when the game is done. Highest possible score should be achieved by starting at a higher level.
      - Save the top 3 values in EEPROM with name and score.
    * Settings:
      - Enter name. The name should be shown in highscore. Maybe somewhere else, as well?
      - Starting level: Set the starting level value. The idea is to be able to start from a higher level as well. Can be replaced with difficulty.
      - LCD contrast control (must replace potentiometer!).
      - LCD brightness control (must change LED wire that’s directly connected to 5v).
      - Matrix brightness control (see function setIntesnity from the ledControl library).
      - Extra stuff can include items specific to the game mechanics, or other settings such as chosen theme song etc.
    * About: 
      - should include details about the creator of the game: at least game name, author and github link (use scrolling text?)
3. While playing the game: display all relevant info
    - Lives
    - Level
    - Score
    - Time?
    - Player name?
    - etc
 4. Upon game ending:
    * Screen 1: 
      - a message such as ”Congratulations on reaching level/score X”. ”You did better than y people.”. etc. 
      - switches to screen 2 upon interaction (button press) or after a few moments.
    * Screen 2: 
      - display relevant game info: score, time, lives left etc.
      - must inform player if he/she beat the highscore. 
      - this menu should only be closed by the player, pressing a button.

# :vulcan_salute: Game requirements

``` PHASE 1,2,3 ```

- Minimal components: an LCD, a joystick, a buzzer and the led matrix.
- You must add basic sounds to the game (when ”eating” food, when dying, when finishing the level etc). Extra: add theme songs.
- It must be intuitive and fun to play.
- It must make sense in the current setup. Study the idea of a panning camera - aka the 8x8 led doesn’t need to be the entire map. It can only be the current field of view of the player.
- The levels must progress dynamically. Aka the level difficulty, score
and other properties should be a function of the level number or time.
However, the challenge here is for it to grow in a playable way - not
too easy for a long time so it becomes boring, not too hard too fast
so it’s not attractive. Also, it’s nice to have an ending, a final level,
a boss etc. It shouldn’t necessarily go on forever (but that’s fine,
though).
- Useful resources:
  - [LedControl library]( http://wayoda.github.io/LedControl/pages/software)
  - [9999 games in one]( https://www.youtube.com/watch?v=RPTanMNGmek)
  - [Cool example of a simple build]( https://www.youtube.com/watch?v=gluRdsmNAwU)
- Example of from previous years, including menu: (they do not
meet the requirements, use only for inspiration!)
  - [Santa’s workshop]( https://www.youtube.com/watch?v=GFQkmgMiz-4) -> nice touch with the songs
  - [Space invaders](https://www.youtube.com/watch?v=QNpVnlfoA0Q) -> good, but should’ve used the extra button as a trigger
  - [Rush hour](https://www.youtube.com/watch?v=x1dpq7ZVwLE) -> great menu, but care too big
  - [Hungry πxl]( https://www.youtube.com/watch?v=-xkd1i6417I) -> should’ve used a blink for player
  - [Racing car](https://drive.google.com/file/d/11A9FUwp7jgpe2jkebaNmO6tHpTHz0t3x/view) -> nice touch with difficulty in settings
  - [Tetris](https://www.youtube.com/watch?v=y1NTdkCfhUc)
  - [Other type of racing game]( https://www.youtube.com/watch?v=P7bDNxj5xQ8)
  - [Pong]( https://www.youtube.com/watch?v=yNq-2f87Ewc) -> too simple now
  - [Tower of Power]( https://www.youtube.com/watch?v=k4eKOsfRSm8) -> too simple and must input name with joystick, not from PC
  - [T-REX run]( https://www.youtube.com/watch?v=FNnYLSPdGB8) -> too simple mechanics
  - [Matrix heroes]( https://www.youtube.com/watch?v=rVG6xQdty2I)
  - [Reverse it]( https://www.youtube.com/watch?v=ipwmN_Qqrns)
  - [Perilous path]( https://drive.google.com/file/d/13Wp0T1PxEz2l59WMqxqNn7WIKvp2JqQh/view)
  - [Snake](https://vimeo.com/307886825)
  - [Tanks]( https://photos.google.com/share/AF1QipPe9G0rZbeXhE3kLTh2TIZrAsjNKgHi_UVzOq6NaGCtsJCHdJwmYUHKM2KYqjSGgg/photo/AF1QipO2QISUSYI9lkNnqdL9NVWhrdaJf_NJgSqPHCLkey=RXdsbmI5QVlINUNxR0JELXQtMldMb0VRRlMzaUhn) -> interesting menu
  - [Flappy bird](https://drive.google.com/file/d/1VHPbNwdJ3gTokfjorNThMMhMGoxdmGS_/view)

# :peacock: Publishing task: github README

- Must be created in ```PHASE 1``` and updated as you progress. 
- ```Publishing task:``` You must add the code to the Github repo and continue updating the
```README``` with at least the following details (but feel free to be more creative):
  1. Task Requirements
  2. Picture of the setup
  3. Link to video showcasing functionality (I recommend youtube, but anything I can access is fine)
  4. Used components
  5. Remember to publish the video in the correct orientation. 
  6. Hand in the homework on MS teams when done - aka when github is up to date

# :t-rex: Development guidelines
1. Create the game in steps. Start with a proof of concept (you need it for first phase anyway) and work up from there. Validate your initial ideas, assumptions and vision. You are graded on your progress as well, not only the final result.
2. Remember that it’s better to have a simple, yet working game, rather than a more complex and buggy one. :lady_beetle: :lady_beetle: :lady_beetle:
3. Make it feel like a complete project as much as possible. Small details and finishing touches separate a prototype from a product.
4. Remember to follow the coding guidelines.
5. Remember that while details are important, the bulk of your grade will come from the fact if it works.
