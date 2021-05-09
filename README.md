<h1 style = "color: rgb(0,162,232);" > Liquid Window <h1> 

<img src = "Logo.png" width = 250/>
<img src = "images/GitHub/Git Hub Description.png">

<h3> Liquid Window is my current effort to make a lightweight class that allows for customization of the Title bar and the window itself. Currently the Title bar is simply a widget, drag functionality exists in the main window area itself. I made this code to help you along on this same journey. I invite you to clone, fork, and make pull requests. I welcome improvements and constructive critiques on my code. You're free to use this in your project. </h3>


<br>

<h3> Liquid Window is based on the resizeable widget code found at https://wiki.qt.io/Widget-moveable-and-resizeable but has been adapted for use as an upper level, parentless Widget. If you need a resizeable Widget this is where you want to go! This class/.h,.cpp file is called tcontiner is included in this repo for your reference.
</h3>

<br>

<h1> Why this code is useful. </h1>

<br>

<h3> If you're delving in QML or doing anything with Qt at some point you will want to customize the look of your application window. This will allow speedier learning and development and ultimately more customization of your application.
</h3>

<br>

<h1> Usage: </h1>
<h3> use it as you would QMainWindow() but instead use LiquidWindow() </h3>

```
#include "LiquidWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LiquidWindow w;
    w.show();
    return a.exec();
}

```

<br>

<h2 style = "color: red" > Feel free to fork, create a pull requests and improve on this code. Feel free to use it in your projects.

<br>

<h1> To Do List: </h1>
<br> 
<ul>
<li> Refine the TitleBar() class </li>
<li> Add buttons to control Min/Max/Restore/Close to TitleBar().</li>
<li> Add functionality that will allow customization via QSS/CSS. </li>
<li> Add functions that will allow customization via C++ function calls. </li>
</ul>

<h3> Credits:
<br>
<ul>
<li> Aleksey Osipov </li>
<li> Joe Farrish </li>
</ul>

