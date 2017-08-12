#### set qualcomm compile enviroment
JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export JAVA_HOME
CLASSPATH=.:$JAVA_HOME/lib:$JAVA_HOME/jre/lib:$JAVA_HOME/lib/tools.jar
PATH=$PATH:$JAVA_HOME/bin:$JAVA_HOME/jre/bin
ANDROID_JAVA_HOME=$JAVA_HOME
export ANDROID_JAVA_HOME

# disable ninja
# export USE_NINJA=false

#### set msm8998 enviroment
source build/envsetup.sh
lunch msm8998-userdebug

#### start jack-admin server
./prebuilts/sdk/tools/jack-admin start-server

