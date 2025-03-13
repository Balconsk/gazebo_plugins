For launch

```
mkdir build
cd ./build
cmake ..
make .
export GZ_SIM_SYSTEM_PLUGIN_PATH=$PWD
cd ..
gz sim hello_world_plugin.sdf -v3
```
