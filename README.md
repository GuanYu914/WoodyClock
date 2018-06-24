# WoodyClock

## Introduction
This is digital clock with avr microconcroller, it provides 3 modes to check time, date and tmeperature. To change mode by 
pressing push button, the information of modes will show on the 7 segment display. Another feature is charging, it can power
with Li battery, at least maintain the power for 3 days. 

## Development Environment

The design of whole PCB is under Kicad 4.0.7, and the source code is under debian linux. You can extract rar which locate in pcb directory, then open this project with Kicad IDE.
<p>You can use below instruction to setup AVR-GCC ToolChain</p>
<pre><code>sudo apt-get update<br>
sudo apt-get upgrade<br>
sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude<br>
</pre></code>

## Preview Display

### Information of Time
Uses 24 hour for displaying.

<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/Time.JPG" width="50%" height="50%">

### Information of Date
Uses cross-displaying.

<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/Date.gif" width="50%" height="50%">

### Information of Temperature
Uses degrees Celsius 

<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/Temp.JPG" width="50%" height="50%">

## Layout of PCB 
<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/PCB.JPG" width="50%" height="50%">

## How to set clock time and date manually.

### Step 1
Remove the module, which be surrounded with the red area, and connect USBASP programmer to ICSP pins. If you don't have USBASP
programmer, buy it online. It doesn't very expensive to get.<br>
<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/BeforeProg.jpg" width="50%" height="50%"><br>
If board is like this, you are ready to program it.<br>
<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/AfterProg.JPG" width="50%" height="50%"><br>

### Step 2
<p>Download this repository.<br>
Move into "src" directory.<br>
Edit "main.c" source code.<br>
PS. You must install vim before you edit it.</p>
<pre><code>git clone https://github.com/GuanYu914/WoodyClock.git<br>
cd src<br>
vim main.c<br>
</code></pre>

### Step 3
Uncomment this fuction.
<br><img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/function.PNG" width="50%" height="50%"><br>
This statement will set year to 2018/6/11, set time to 15:8.<br>
You can modifly function parameter to adjust time correctly.

### Step 4
<p>Compile and upload code.<br>
Move into "src" directory.<br>
Type "make flash".<br></p>
<pre><code>make flash
</code></pre>

### Step 5
<p>Don't forget to comment this function, then upload again.<br>
<img src="https://github.com/GuanYu914/WoodyClock/blob/master/photos/function.PNG" width="50%" height="50%"><br></P>
