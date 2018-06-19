# WoodyClock

## Introduce
This is digital clock with avr microconcroller, it provides 3 modes to check time, date and tmeperature. To change mode by 
pressing push button, the information of modes will show on the 7 segment display. Another feature is charging, it can power
with Li battery, at least maintain the power for 3 days. 

## Display Preview

### Time Information
Uses 24 hour for displaying.

<img src="https://github.com/GuanYu914/WoodyClock/blob/master/Time.JPG" width="50%" height="50%">

### Date Information
Uses cross-displaying.

<img src="https://github.com/GuanYu914/WoodyClock/blob/master/Date.gif" width="50%" height="50%">

### Temperature Information
Uses degrees Celsius 

<img src="https://github.com/GuanYu914/WoodyClock/blob/master/Temp.JPG" width="50%" height="50%">

## PCB Layout 
<img src="https://github.com/GuanYu914/WoodyClock/blob/master/PCB.JPG" width="50%" height="50%">

## How to set clock time and date manually.

### Step 1
<p>Download this repository.<br>
Move into "src" directory.<br>
Edit "main.c" source code.<br>
PS. You must install vim before you edit it.</p>
<pre><code>git clone https://github.com/GuanYu914/WoodyClock.git<br>
cd src<br>
vim main.c<br>
</code></pre>

### Step 2
Uncomment this fuction.
<br><img src="https://github.com/GuanYu914/WoodyClock/blob/master/function.PNG" width="50%" height="50%"><br>
This statement will set year to 2018/6/11, set time to 15:8.<br>
You can modifly function parameter to adjust time correctly.

### Step 3
<p>Compile and upload code.<br>
Move into "src" directory.<br>
Type "make flash".<br></p>
<pre><code>make flash
</code></pre>

### Step 4
<p>Don't forget to comment this function, then upload again.<br>
<img src="https://github.com/GuanYu914/WoodyClock/blob/master/function.PNG" width="50%" height="50%"><br></P>
