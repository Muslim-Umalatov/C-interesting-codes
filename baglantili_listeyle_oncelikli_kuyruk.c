/*
 * Veri Yapiları dersi
 * Bağlantılı Listeyle Öncelikli Kuyruk Yapısı
 * Muslim Umalatov 2023 Ödev 3
 * 
 * Hedef:
 * Aşağıdaki önceliklere göre bağlı liste yapısında C uygulama kodunu yazmanız gerekiyor. 
 * Öncelikler: Kuyruğa gelecek olan kişinin ID numarası istenir. Eğer 
 * ID=1 ise sıradan müşteri normal bir şekilde kuyruğun sonuna eklenir.
 * ID=2 bankanın özel müşterileri olduğu için yarı önceliklidir. Kuyruğun en başındaki kişinin 2 arkasına geçer.
 * ID=3 ise 65 yaş üstü olduğu için kuyruğun en başına geçer. 
 *
 * Kuyruğa kişi ekleme, kuyruktan kişiyi işleme alma ve kuyruğu görüntüleme menülerini yazınız.
 *
 * Tüm örnek senaryoları:
 * 1) 
 * INPUT: ID=1, ID=1, ID=1, ID=3
 * OUTPUT: ID=3, ID=1, ID=1, ID=1
 * 2) 
 * INPUT: ID=3, ID=1, ID=3, ID=1, ID=2, ID=1
 * OUTPUT: ID=3, ID=3, ID=2, ID=1, ID=1, ID=1
 * 3) Ek senaryo: 
 * INPUT: ID=3, ID=3, ID=1, ID=2, ID=3, ID=2, ID=1
 * OUTPUT: ID=3, ID=3, ID=2, ID=3, ID=2, ID=1, ID=1
 */

#include <stdio.h>
#include <stdlib.h>

/* Kişi bilgilerini tutan düğüm yapısı */
typedef struct node {
    int id;
    struct node* next;
} node;

node *front = NULL;
node *rear = NULL;

void kuyruga_ekle(int id);
void musteri_isle();
void kuyrugu_goruntule();

int main(int argc, char *argv[]) {
    int secim, id;

    do {
        printf("\n1. Kisi Ekle\n");
        printf("2. Kisi Isle\n");
        printf("3. Kuyrugu Goruntule\n");
        printf("4. Cikis\n");
        printf("\nSeciminiz: ");
        scanf("%d", &secim);

        switch(secim) {
            case 1:
                printf("\nKisi ID'sini girin: ");
                scanf("%d", &id);
                kuyruga_ekle(id);
                break;
            case 2:
                musteri_isle();
                break;
            case 3:
                kuyrugu_goruntule();
                break;
            case 4:
                break;
            default:
                printf("Yanlis bir deger girdiniz!\n");
        }
    } while (secim != 4);

    return 0;
}

/* Kuyruğa kişi ekleme fonksiyonu */
void kuyruga_ekle(int id) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->id = id;
    newNode->next = NULL;

    if (front == NULL) {
        /* Kuyruk boşsa */
        front = rear = newNode;
    } else {
        /* Kuyruk boş değilse */
        if (id == 3) {
            /* ID=3 ise başa ekleme */
            newNode->next = front;
            front = newNode;
        } else if (id == 1) {
            /* ID=1 ise sona ekleme */
            rear->next = newNode;
            rear = newNode;
        } else if (id == 2) {
            /* ID=2 ise 2. sıradan ekleme */
            /* Kuyrukta 2'den çok müşteri varsa */
            if (front != NULL && front->next != NULL && front->next->next != NULL) {
                newNode->next = front->next->next;
                front->next->next = newNode;
            } else {
                /* Yeterli eleman yoksa kuyruğun sonuna ekleme */
                if (rear != NULL) {
                    rear->next = newNode;
                    rear = newNode;
                }
            }
        }
    }
}

/* Kuyruktan kişi işleme alma fonksiyonu */
void musteri_isle() {
    if (front == NULL) {
        printf("\nKuyruk bostur!\n");
    } else {
        node *temp = front;
        front = front->next;
        free(temp);

        if (front == NULL) {
            rear = NULL;
        }
    }
}

/* Kuyruğu görüntüleme fonksiyonu */
void kuyrugu_goruntule() {
    node* temp = front;

    if (front == NULL) {
        printf("\nKuyruk bostur!\n");
        return;
    } else {
        printf("\nKuyruk:\n\n");
        while (temp != NULL) {
            printf("ID%d ", temp->id);
            temp = temp->next;
        }
    }
    
    printf("\n");
}