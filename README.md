###### Instituto Politécnico do Cávado e Ave  
###### Licenciatura em Engenharia de Sistemas Informáticos  
###### Sistemas Embebidos e de Tempo Real  
###### 2017/18  


# __Enunciado do Trabalho Prático 1__
  
  
## __Objectivos__
  Com este trabalho pretende-se dar aos alunos a oportunidade de aplicarem alguns conceitos de programação para sistemas embebidos (p.e. microcontroladores) e de sistemas operativos de tempo real. Os alunos desenvolverão um projeto, dividido em 2 programas distintos (“baremetal” + FreeRTOS), que deverá adquirir várias fontes de sinais analógicos e digitais replicando o funcionamento de um volante de competição. Este programas devem ser desenvolvidos com a plataforma Arduino. Este trabalho culminará num relatório que deverá ser entregue ao docente, para além de um vídeo demonstrativo, ficheiros auxiliares e ficheiros com o código fonte devidamente comentado.  
  
  
## __Realização do trabalho prático__  
Os alunos deverão implementar um modelo matemático do comportamento de um automóvel (o mais fiável possível), implementando obrigatoriamente as seguintes funcionalidades:  
1. Controlo da rotação do volante através do ângulo estimado pelo sensor de gravidade (acelerómetro).  
2. Velocidade progressiva de acordo com a pressão exercida no acelerador (sensor de força) e na mudança atual.  
3. Desaceleração/Travagem progressiva de acordo com a pressão e exercida no travão (sensor flex).  
4. Luz de indicação de mudança de direção (esquerda e direita)  
	__Valorizações:__ modo blink e modo 4-piscas;  
5. Luzes crescentes para indicação no nível de rotação do motor.  
	__Valorizações:__ padrão para indicação de mudança em Reserve;  
6. Aviso sonoro para alteração de mudança (apenas na subida de mudança).  
	__Valorizações:__ aviso sonoro para mudança em Reverse;  
7. Leitura de botões para mudança de direção e atuação dos indicadores.  
	__Valorizações:__ modo 4-piscas;  
8. Leitura de botões para subir e descer as mudanças do modelo de carro.  
	__Valorizações:__ padrão para ligar e desligar o carro;  
9. Envio para o computador do estado do carro, incluindo, mas não limitado ao angulo direção, velocidade, rotação, mudança atual, piscas, pressão nos pedais.  
  
O volante inteligente deve ser implementado com um Arduino Uno (ou similar) e de acordo com o esquema presente neste enunciado. O código deve ter como base de implementação o FreeRTOS.  
  
## __Relatório__  
  
O trabalho deverá ser desenvolvido em grupos de 2 ou 3 elementos. O grupo deverá elaborar um relatório escrito, que reflita e descreva o trabalho desenvolvido, as dificuldades sentidas e a resolução encontrada para as mesmas. O relatório deverá ter um mínimo de 5 páginas e um máximo de 15 páginas, excluindo listagens, capas, índices e anexos.  
  
![Imagem 1](/IMAGES/imagemEnunciado.jpg)
  

## __Avaliação__  
  
Serão tomados como critérios de avaliação os seguintes factores:  
  
* Qualidade do programa o desenvolvimento das funcionalidades descritas no enunciado do trabalho  
* demonstração do funcionamento correto do programa  
* Qualidade do relatório  
* descrição correcta e completa da estrutura do programa  
* descrição das técnicas aplicadas no desenvolvimento das funcionalidades  
* Qualidade da defesa individual  
* avaliação do conhecimento de cada elemento do grupo  
* Respeito pelas regras de entrega do relatório, ficheiros auxiliares e ficheiros com o código fonte  
  
A natureza colectiva da realização de um trabalho em grupo não prejudica o facto de a avaliação ser individual para cada um dos elementos do grupo.  
  
## __Prazos__  
  
A realização do trabalho pressupõe a entrega do relatório, do programa compilado, dos ficheiros com o código fonte e eventuais ficheiros auxiliares, tudo em formato digital.  
A entrega do relatório e restantes ficheiros será efectuada através do moodle. O relatório e restantes ficheiros deverão ser colocados num ficheiro zip com o nome “ESIPL-SETR-T1-xxxxx-yyyyy”, em que xxxxx e yyyyy deverão ser preenchidos com os números de aluno de cada um dos elementos do grupo.  
O prazo de entrega do relatório e restantes elementos é o dia 30 de abril de 2017, às 23:55. Qualquer eventual atraso na entrega destes elementos implicará uma penalização na nota dos elementos do grupo, à razão de 0,5 valores por cada dia de atraso.  
  
## __Conduta ética__  
  
A falta de transparência em avaliações, presenciais ou não, é naturalmente ilegal e imoral. Todas as fontes utilizadas para suporte a trabalhos devem ser obrigatoriamente e claramente referenciadas. Qualquer plágio, cópia ou conduta académica imprópria será penalizada.  
