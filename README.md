# CoLiNa-Engine

The CoLiNa-Engine (COmmand LIne NArration Engine) is a WIP small engine for creating and playing command-line games defined in a simple but powerful XML-based syntax.

This engine is still in a very early state, but it should be enough to give a glimpse of its capabilities. Future work is indicated in the section [Future work](#future-work)

## How to compile and run the engine

Just download and unzip the repo in any location you want. Open a terminal, navigate to where you unzipped the repo, and run:

`make`

And you're ready to go play!

## Game structure and behavior

The game itself is composed by a set of certain elements: *Areas, Items, Commands* and *Actions*. These elemets are structured in the following way:

* The game itself is defined as a set of areas.
* Each area has a set of items.
* Each item can be in a certain state, and in each state, various commands can be executed.
* Each command is composed by a list of runnable actions.

The game behavior itself is very simple: it reads user input (given on the form of command-item, such as "grab key", "open door", etc.), and **executes the given command on the given item (if its state permits that) on the player's current area**. The engine alerts if the player cannot perform the command (for example, the item may not exist or it may not be in a state suitable for that command). When a command is run, its actions are executed in sequential order. The actions are a key component in the engine, since they allow for manipulation of the states of the objects, printing text, telling the engine to end the game, etc. Actions to be added in the future are indicated in the section [Future work](#future-work).

## Game file syntax

The following file is a simple example of a game file, which is written in an XML-like syntax.

```xml
<Game>
  <Area name="area1" text="Sample text" startingZone="true">
    <Item name="switch" state="state1">
      <State name="state1">
        <Command name="touch">
          <Action name="print" text="You have touched the switch"/>
        </Command>
      </State>
    </Item>
  </Area>
</Game>
```
As it can be seen, this file conforms to the game structure explained in [Game structure](#game-structure-and-behavior). In addition to this structure, the XML file specifies additional information for each element:

* **Area**: the file specifies, for each area, its *name* (with the attribute `name`), its *description* (with the attribute `text`), and a true-false value indicating if this area is the starting point (with the attribute `startingZone`). Note that only one area can be defined as the starting one: the engine will give an error if multiple starting areas are defined.
* **Item**: the file specifies, for each item, its *name* (with the attribute `name`), and its *initial state* (with the attribute `state`). Please note that the engine will only check if an state does not exist if it tries to run a command on that object, and it finds that its current state does not match with any given state. This is an issue to be solved in the future.
* **State**: the file specifies, for each state, its *name* (with the attribute `name`).
* **Command**: the file specifies, for each command, its *invocation name* (with the attribute `name`).
* **Action**: the file specifies, for each action, its *action name* (with the attribute `name`), and a list of action-specific parameters. The current set of actions is further explained on Section [Current action set](#current-action-set)

## Current action set

As it has been said before, the actions are one of the most crucial elements in the engine, since they allow for manipulating various aspects of the game. The current action set is the following one (each entry indicates the action *invocation name*, what it does, and its list of parameters):

* `print`: this action prints a given text to the command-line terminal. It has one parameter:
  * `text`: the text to be printed

* `setState`: this action changes the state of a given item **in the current area** to a certain given state. It has two parameters:
  * `item`: the item which state is going to be changed.
  * `state`: the new state to give to the item.
  
* `endGame`: this action tells the game engine to finish the game. It has no parameters

## Expanding the action set and modifying the engine

For more information on how to add new actions to the game and how to modify the engine, please visit the [Wiki](https://github.com/Yxuer/CoLiNa-Engine/wiki).

## Future work

The engine is still in a very early state. Because of this, there is still a lot of functionality to be added:

* This engine could hugely benefit from a GUI for game edition. However, my knowledge about interface programming is zero, so this will have to wait for a long time.
* The current action set is very limited, and there are various actions that can be added to the engine. For example, player inventory actions, variable manipulation actions, etc.
* There is a special kind of action to be added to the game, the *trigger*. The trigger checks if a list of conditions is true and, in that case, runs a certain set of actions. If the list is false, it runs another set of actions.
* In addition to triggers, *conditions* must also be implemented.
* Some minor improvements must also be made (like duplicated-name checking).
