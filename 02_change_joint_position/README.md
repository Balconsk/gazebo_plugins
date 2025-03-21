Это переписаный пример для JointPositionRandomizer взятый с гитхаб gz sim 8 

## Build

~~~
mkdir build
cd build
cmake ..
make
~~~

## Run

Add the library to the path:

~~~
cd ..
export GZ_SIM_SYSTEM_PLUGIN_PATH=`pwd`/build
~~~

Then run a world that loads the plugin as follows:

    gz sim -r -v 4 joint_position_changer.sdf