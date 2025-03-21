For launch

```
mkdir build
cd ./build
cmake ..
make .
cd ..
export GZ_SIM_SYSTEM_PLUGIN_PATH=`pwd`/build
ign gazebo hello_world_plugin.sdf -v3
```
