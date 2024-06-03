# Repositorio para salvar progresso nos estudos de ROS para projeto Petrobras

Obs: Decidi propositalmente incluir a pasta de configuração do vscode `.vscode` para salvar as configurações de inclusão de dependências em `C++` para __ROS__.

---

## Usando docker + Exemplo com ros services

Com a imagem do __ROS Noetic__ funcionando, basta encontrar seu id com:

```bash
    sudo docker ps -a
```

Supondo, por exemplo, que o id do container seja `ae5c9f316035`, podemos abrir várias sessões de bash em outros terminais para realizar comandos dentro deste container, como:

```bash
    sudo docker exec -it ae5c9f316035 bash
    # vai executar o comando bash no container ae5c9f316035

    cd home/ROS/ros_ws # acessa o workspace principal do container, e estamos prontos!

```

## Exemplo de uso com servidor e cliente

Primeiro, após todos os passos para a compialação da imagem do __ROS Noetic__ (customizada pelo LabRom), iniciamos um container com o comando abaixo:

```bash
    sudo ./docker/scripts/run.sh
    cd home/ROS/ros_ws
    
```

Agora, o volume `ros_ws` está espelhado com o volume real. Isso significa que todas as alterações em `ros_ws`, tanto dentro quanto fora do container serão aplicadas a outra parte. Assim, podemos copiar todo o pacote `simpleps` deste respositório para dentro de `ros_ws/src` na mão ou com o comando abaixo (em outro terminal!!):

```bash
    cp {caminho/para/este/repo}/labrom-ros-studies/src/simpleps {caminho/para/ros/docker}/ros_ws/src/ -r
```

Agora, no primeiro terminal, que está conectado no container do ROS, podemos compilar e rodar o roscore:

```bash
    catkin_make # dentro de home/ROS/ros_ws
    roscore
```

Usando o comando para executar bash dentro do container a partir de outros terminais (mostrado nas seções anterioes a esta), podemos abrir dois e executar o serviço de adicionar inteiros:

```bash
    rosrun simpleps server_addints 
```

Em outro terminal, faremos o mesmo, porém chamando agora o `client`:

```bash
    rosrun simpleps client_addints 10 15
```

Se tudo foi realizado corretamente, vamos ober a resposta:

```bash
    [ INFO] [1715347450.069832549]: Requisicao solicitada: 10 + 14
    [ INFO] [1715347450.069858095]: Resposta: 24
```

## Instalalando catkin tools

Para usar `catkin build`, devemos instalar os pacotes separadamente:

```bash
    sudo apt install ros-noetic-catkin
    sudo apt install python3-catkin-tools
    sudo apt install python3-osrf-pycommon
```

## Curso ETH Zurich

Dependências adicionais:

```bash
    sudo apt-get install ros-noetic-hector-gazebo-plugins
    # sudo apt install python3-catkin-tools

    sudo apt-get install ros-noetic-velodyne-description
    sudo apt-get install -y ros-noetic-twist-mux
    sudo apt-get install -y ros-noetic-robot-localization
    sudo apt-get install -y ros-noetic-pointcloud-to-laserscan
    sudo apt-get install -y ros-noetic-velodyne-simulator 
    sudo apt-get install -y ros-noetic-velodyne-description

```

Por: José Carlos Andrade do Nascimento
