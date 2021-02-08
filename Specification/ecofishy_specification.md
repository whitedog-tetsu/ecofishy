
<div style="text-align: center;">

# Ecofishy Specification

</div>

## <a id="index" href="#index">Contents</a>

- [Ecofishy Specification](#ecofishy-specification)
  - [<a id="index" href="#index">Contents</a>](#contents)
- [<a id="section1" href="#section1">Abstract</a>](#abstract)
- [<a id="section2" href="#section2">System component</a>](#system-component)
- [<a id="section3" href="#section3">State transition</a>](#state-transition)
- [<a id="section4" href="#section4">Compute</a>](#compute)
- [<a id="section5" href="#section5">Wireless communication sequence</a>](#wireless-communication-sequence)
- [Data format](#data-format)
- [<a id="section6" href="#section5">Sensor node operating flow</a>](#sensor-node-operating-flow)
- [<a id="section7" href="#section6">Control sensor node</a>](#control-sensor-node)
- [Configuration format](#configuration-format)

# <a id="section1" href="#section1">Abstract</a>  
Ecofishy realizes to monitor the environment of fish tank, control the equipments such as the feed machine and the heater, and also you can access the visualized information of environmental data.

This system is dedicated to owner of animal, learn ecology system, electric hobby and programming in education.

You can get more information about ecology system, electric knowledge, and the source code check our website.
"www.echofishy.sugee.com" 

<b>Let's Enjoy it!</b>



# <a id="section2" href="#section2">System component</a>  
![System component](../out/Specification/system_component/system_component.png)   

Ecofishy is composed of the Application for user and sensor nodes to monitor fish tank. 

The application recieves data by wireless communication and shows the data graph.



# <a id="section3" href="#section3">State transition</a>  
![statement transition](../out/Specification/sensor_node_statement/sensor_node_statement.png)   

<p class="ec__link-index"><a href="#index">[to the Constents]</a></p>


# <a id="section4" href="#section4">Compute</a>
![Compute](../out/Specification/sensor_node_flow_chart/Sensor_Node_Operating_Flow.png)

<p class="ec__link-index"><a href="#index">[to the Constents]</a></p>


# <a id="section5" href="#section5">Wireless communication sequence</a>
![Wireless communication](../out/Specification/Wi-SUN_sequence/Wi-SUN_sequence.png)

# Data format
SN + data + system status
SN: sequence number
data: sensor data
systeme status: show working well or not

<p class="ec__link-index"><a href="#index">[to the Constents]</a></p>

# <a id="section6" href="#section5">Sensor node operating flow</a>
![Sensor node operating flow](../out/Specification/sensor_node_flow_chart/Sensor_Node_Operating_Flow.png)


# <a id="section7" href="#section6">Control sensor node</a>
User selectable parameters are below.

| Name        | value         | Description |
|-------------|---------------|-------------|
| Sleep time  | 1 - 6000 sec  |             |
| Sensor type |               |             |



# Configuration format
Configuration format follows json style format.

{"Key name": "value"}
value can be number, character, boolean.

{"SleepTime": "1000"}


| Key name    | value         | Description |
|-------------|---------------|-------------|
| SleepTime   | 1 - 6000 sec  |             |
| SensorType  |               |             |
| CH          |               |             |



