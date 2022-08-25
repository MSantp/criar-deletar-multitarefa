#define LED_B 2
#define LED_G 0
#define LED_R 5

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

void vTaskInvertPino(void *pvParameters);
void vTaskDebugSerial(void *pvParameters);

void setup() {

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  Serial.begin(9600);
  xTaskCreate(vTaskInvertPino, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1Handle);
  xTaskCreate(vTaskDebugSerial, "Task2", configMINIMAL_STACK_SIZE + 1024, NULL, 2, &task2Handle);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
  for (;;) {

  }
}

void vTaskInvertPino(void *pvParameters) {
  int estadoPino = 0;
  for (;;) {
    estadoPino = !estadoPino;
    digitalWrite(LED_R,estadoPino);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void vTaskDebugSerial(void *pvParameters) {
  int cont = 0;
  for(;;){
    Serial.println("Task Debug: " + String(++cont));

    if(cont==5){
      Serial.println("Suspendendo a vTaskInvertPino...");
      vTaskSuspend(task1Handle);
      digitalWrite(LED_R,LOW);
    }else if(cont==10){
      Serial.println("Reiniciando a vTaskInvertPino...");
      vTaskResume(task1Handle);
      cont=0;
    }
    
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
 }
