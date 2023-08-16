int main() {
    char* p = "13";
    int i = strtol(p, &p, 10);
    printf("%d\n", i);
}