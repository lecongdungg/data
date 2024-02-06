#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

FILE *fp;
int a, b, c, d, lv;
float t, idy;
int idx = 1;
int nx = 16000;
char buffer[9999];

void scan(int a, int b, int c, int d, float t);
void get();
void banner();

int main() {

    int a, b, c, d, e, n;

    banner();

    int ck;
    char buf[25];

    printf("\033[1;33mKiểm tra xác nhận...\033[0m\n");

    printf("\033[1;35mTrạng thái: Premium\033[0m\n");

    printf("\033[1;34mKhông hết hạn\033[0m\n");

    sleep(1);
    system("date +%y%m%d >vr");
    FILE *px = fopen("pirs", "r");

    if(px != NULL) {
        printf("\033[1;31mThời gian dùng thử của bạn đã hết, vui lòng liên hệ tác giả\033[0m\n");
        return 0;
    }
    else {
        FILE *pF = fopen("vr", "r");

        if(pF == NULL) {
            printf("\033[1;31mXác nhận thất bại! Chương trình này không thể chạy trên thiết bị này\033[0m\n");
            return 0;
        }
        else {
            fscanf(pF, "%d", &ck);

            int cr = 300512;
            system("date +%H%M >sgr");

            FILE *sG = fopen("sgr", "r");
            fscanf(sG, "%d", &lv);

            if(ck >= cr && lv >= nx) {
                printf("\033[1;31mThời gian dùng thử của bạn đã hết, vui lòng liên hệ tác giả\033[0m\n");
                snprintf(buf, 25, "echo \"\" >pirs");
                system(buf);
                system("cp pirs $PREFIX/bin/pirs");
                return 0;
            }
            else {
                printf("\033[1;32mTài khoản hợp lệ √\033[0m\n");
            }
        }
    }

    printf("\033[1;31m\nNhập khoảng địa chỉ IP theo định dạng CIDR: \033[0m");
    scanf("%d.%d.%d.%d/%d", &a, &b, &c, &d, &e);
    printf("\033[1;34m\nNhập thời gian kết nối timeout: \033[0m");
    scanf("%f", &t);

    switch(e) {
        case 24:
            n = 255;
            d = 0;
            for(d = 0; d <= n; d++) {
                scan(a, b, c, d, t);
            }
            break;

        case 16:
            n = 2505;
            for(d = 0; d <= n; d++) {
                for(c = 0; c <= n; c++) {
                    scan(a, b, c, d, t);
                }
            }
            break;

        default:
            printf("\033[1;31mPhân khúc mạng chưa được triển khai\033[0m\n");
            return 0;
    }

    if(e == 24) {
        d = 0;
    }
    else if(e == 16) {
        c = 0;
        d = 0;
    }

    banner();
    printf("\033[1;34mKết quả quét của \033[0m");
    printf("\033[1;32m%d.%d.%d.%d/%d\033[0m\n\n", a, b, c, d, e);
    FILE *fp1 = fopen("bugs", "r");

    if(fp1 == NULL) {
        printf("\033[1;31mKhông tìm thấy máy chủ!\033[0m");
        return 0;
    }

    get();
    system("cat bugs >> hosts.txt");
    system("rm bugs");
    printf("\033[1;34mĐã lưu vào \033[0m");
    printf("\033[1;32mhosts.txt\033[0m\n\n");


    return 0;
}

void scan(int a, int b, int c, int d, float t) {
    int lv;

    system("date +%H%M >sgr");

    FILE *sG = fopen("sgr", "r");
    fscanf(sG, "%d", &lv);

    if(lv >= nx) {
        printf("\033[1;31mThời gian dùng thử của bạn đã hết, vui lòng liên hệ tác giả.\033[0m\n");
    }
    else {
        char buf[250];
        double m = t;
        snprintf(buf, 250, "\ncurl https://%d.%d.%d.%d --tlsv1.2 --tls-max 1.2 --connect-timeout %.4f -m %.4f -k -o /dev/null -s -w \"%%{remote_ip} timeout!: %%{response_code}\\n\" > host.txt", a, b, c, d, t, m);
        char fast[50];
        char second[50];
        char buk[250];
        int sts;
        system(buf);
        FILE *fptr;
        FILE *fptr1;
        FILE *fptr2;
        FILE *fp1;

        fptr = fopen("host.txt", "a");
        fptr1 = fopen("host.txt", "a");
        fptr2 = fopen("host.txt", "a");

        fptr = fopen("host.txt", "r");
        fscanf(fptr, "%s", fast);

        system("cut -f 2- -d ' ' host.txt > host1.txt");

        fptr1 = fopen("host1.txt", "r");
        fscanf(fptr1, "%s", second);
        system("cut -f 2- -d ' ' host1.txt > host2.txt");

        fptr2 = fopen("host2.txt", "r");
        fscanf(fptr2, "%d", &sts);

        if(sts == 000) {
            printf("\033[1;31m%s\033[0m\n", fast);
        }
        else {
            printf("\033[1;32m%s\033[0m ", fast);
            printf("\033[1;32m√\033[0m\n");
            snprintf(buk, 250, "echo \"%d.%d.%d.%d\" >>bugs", a, b, c, d);
            system(buk);
        }
    }
}

void get() {
    FILE *fp1 = fopen("bugs", "r");

    while(fgets(buffer, 9999, fp1) != NULL) {
        printf("\033[1;32m%s\033[0m\n", buffer);
    }
}
    
void banner() {
    system("clear");

    printf("╔╗─╔╗─────╔╗╔═══╗\n");
    printf("║║─║║────╔╝╚╬╗╔╗║\n");
    printf("║╚═╝╠══╦═╩╗╔╝║║║╠╦══╦══╦══╦═╗\n");
    printf("║╔═╗║╔╗║══╣║─║║║╠╣╔╗║╔╗║║═╣╔╝\n");
    printf("║║─║║╚╝╠══║╚╦╝╚╝║║╚╝║╚╝║║═╣║\n");
    printf("╚╝─╚╩══╩══╩═╩═══╩╩═╗╠═╗╠══╩╝\n");
    printf("─────────────────╔═╝╠═╝║\n");
    printf("─────────────────╚══╩══╝\n");
    printf("v1.0.1\n");
}
