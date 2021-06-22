# TB3_proj1

 아래의 조건을 만족하는 Program을 작성하고 로봇 시스템에 적용

### A.	창 1, 2, 3에 각각에 서로 다른 publisher에서


창 1 : 모터 On(1)/Off(0)

창 2 : 모터속도(0~1 사이값)

창 3 : 라이다 센서 각도(0~359 사이값) 두 개  (ex, 15 80) 입력 한다.

(반복해서 넣을 수 있게, 다른 값을 넣으면 그 값으로 바뀌게)


### B.	모터가 On 시

i.	로봇이 각 방향으로 45도 이상 기울였을 때는 모터가 구동되지 않음 

ii.	창2에서 넣은 두 개 값 사이 각도에 거리 최소가 30cm 이내인 경우 모터 정지, 30cm 이상인 경우 모터 구동

  (예를 들면 창3에 15 80 입력시 15~80도 사이에 30cm 이내에 물체가 있으면 모터정지)

iii.	창2의 두 값 사이의 각도에 있는 최소 거리를 1초에 한번씩 창4의 화면에 Print

(예를 들면 15~80도 사이에 45도에 가장 로봇과 가까운 물체가 있는 경우 그 값을 출력)

iv.	창 5에 로봇 전방으로 기울어진 각도, 좌우로 기울어진 각도를 100ms에 한번씩 Print


### C.	Motor Off 명령 입력 시 어떠한 상황에서도 모터 구동하지 않음


#### [1step] : roslaunch turtlebot3_bringup turtlebot3_robot.launch
#### [2step] : rosrun rosrun midterm_kmg mid_1
#### [3step] : rosrun rosrun midterm_kmg mid_2
#### [4step] : rosrun rosrun midterm_kmg mid_3
#### [5step] : rosrun rosrun midterm_kmg mid_4
#### [6step] : rosrun rosrun midterm_kmg mid_5

### 작동 영상
https://www.youtube.com/watch?v=E6v_uOKAEnQ

