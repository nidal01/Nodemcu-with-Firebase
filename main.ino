#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

// Firebase veritabanı adresi, Token ve Wi-Fi ağ bilgileri
#define FIREBASE_HOST "" // HTTP veya HTTPS olmadan yazın
#define FIREBASE_AUTH ""
#define WIFI_SSID "5g"
#define WIFI_PASSWORD "12345678"

// Firebase veritabanı nesnesi
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Wi-Fi ağına bağlanma
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("WiFi bağlantısı kuruluyor");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP adresine bağlandı: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Firebase bağlantısını başlatma
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // GPIO 2 pinini çıkış olarak ayarlama ve başlangıçta düşük seviyeye ayarlama
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  // Firebase'den veri alınması
if (Firebase.getString(FirebaseData(), "/led"))
 {
    // Veri başarıyla alınırsa
    if (firebaseData.stringData() == "1") {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
  } else {
    // Veri alınamazsa hata mesajını yazdırma
    Serial.print("Veri alınamadı: ");
    Serial.println(firebaseData.errorReason());
  }

  // İsteğe bağlı olarak diğer işlemler burada yapılabilir
}
