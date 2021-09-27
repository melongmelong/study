struct domain{
    char domain[100];
    char localpart[100][100];
    int cnt_local;
};

int numUniqueEmails(char ** emails, int emailsSize){
    struct domain domains[100];
    int domain_cnt=0;
    char local[100], domain[100];
    int i, j, k, flag;
    int ans=0;
    
    memset(&domains, 0, sizeof(domains));
    
    for(i=0; i<emailsSize; i++){
        k = 0;
        flag = 0;
        for(j=0; emails[i][j]!='@'; j++){
            if(emails[i][j] == '.'){
                continue;
            }
            if(emails[i][j] == '+'){
                flag = 1;
            }
            if(flag){
                continue;
            }
            local[k] = emails[i][j];
            local[k+1] = '\0';
            k++;
        }
        strcpy(domain, &emails[i][j+1]);
        
        for(j=0; j<domain_cnt; j++){
            if(strcmp(domains[j].domain, domain) == 0){
                break;
            }
        }
        if(j==domain_cnt){
            strcpy(domains[domain_cnt].domain, domain);
            domain_cnt++;
        }
        
        for(k=0; k<domains[j].cnt_local; k++){
            if(strcmp(domains[j].localpart[k], local) == 0){
                break;
            }
        }
        if(k<domains[j].cnt_local){
            continue;
        }
        strcpy(domains[j].localpart[domains[j].cnt_local], local);
        domains[j].cnt_local++;
        
        ans++;
    }
    
    return ans;
}
