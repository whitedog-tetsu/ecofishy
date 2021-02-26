
<div style="text-align: center;">

# Ecofishy Specification

</div>


- [Ecofishy Specification](#ecofishy-specification)
- [<a id="section1" href="#section1">Abstract</a>](#abstract)
- [<a id="section2" href="#section2">System component</a>](#system-component)
- [<a id="section3" href="#section3">Statemachine</a>](#statemachine)
- [<a id="section4" href="#section4">Compute</a>](#compute)
- [<a id="section5" href="#section5">Wireless communication sequence</a>](#wireless-communication-sequence)
- [Data format](#data-format)
- [<a id="section6" href="#section5">Sensor node operating flow</a>](#sensor-node-operating-flow)
- [<a id="section7" href="#section6">Control sensor node</a>](#control-sensor-node)
- [<a id="section7" href="#section7">Configuration format</a>](#configuration-format)

# <a id="section1" href="#section1">Abstract</a>  
Ecofishy realizes to monitor the environment of fish tank, control the equipments such as the feed machine and the heater, and also you can access the visualized information of environmental data.

This system is dedicated to owner of animal, learn ecology system, electric hobby and programming in education.

You can get more information about ecology system, electric knowledge, and the source code check our website.
"www.echofishy.sugee.com" 

<b>Let's Enjoy it!</b>



# <a id="section2" href="#section2">System component</a>  
@import "system_component.puml"

Ecofishy is composed of the Application for user and sensor nodes to monitor fish tank. 

The application recieves data by wireless communication and shows the data graph.



# <a id="section3" href="#section3">Statemachine</a>  
@import "sensor_node_statement.puml" 
<p class="ec__link-index"><a href="#index">[to the Constents]</a></p>


# <a id="section4" href="#section4">Compute</a>
@import "sensor_node_flow_chart.puml"

<p class="ec__link-index"><a href="#index">[to the Constents]</a></p>


# <a id="section5" href="#section5">Wireless communication sequence</a>
@import "Wi-SUN_sequence.puml"

# Data format
SN + data + system status
SN: sequence number
data: sensor data
systeme status: show working well or not

<p class="ec__link-index"><a href="#index">[to the Constents]</a></p>

# <a id="section6" href="#section5">Sensor node operating flow</a>
@import "sensor_node_flow_chart.puml"


# <a id="section7" href="#section6">Control sensor node</a>
User selectable parameters are below.


| Key name    | value         | Description |
|-------------|---------------|-------------|
| SleepTime   | 1 - 6000 sec  | Decimal     |
| SensorType  | Sensor Node:0, Host:1  |             |
| CH          | 21 - 38                | Decimal            |
| Low Power   | 0: Disable, 1: Enable     |             |
| LED color   | 0: red, 1: green, 2: blue, 3: purple, 4: yellow, 5: aqua, 6: white | |
| LED brightness | 0 - 255 | |
|Node No | auto numbering | Connected sensor node|

# <a id="section7" href="#section7">Configuration format</a>

Configuration format is json style.
values can be number, character, boolean.

{"Key name": "value"}

ex.
{"SleepTime": "1000"}
{"SensorType": "1"}
{"NodeNo": }




