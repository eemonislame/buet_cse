#include<stdio.h>
int main()
{
    int n, m, itm_code[101], price[101], stock[101], gross=0, ttl_dmnd=0, served, initial[101];
    int requested_code[1001], requested_qnt[1001], demand[101]={0}, sold[101]={0}, min_code;
    int invalid=0, full=0, part=0, rjtd=0, ttl_sld=0, grs_sls=0, ttl_dis=0, lst_dmnd=0;
    int mst_dmnd=0, mst_dmnd_code, mst_sld=0, mst_sld_code, h_rev_code;
    int discount, bill, rev[101]={0}, h_rev=0, net=0;


    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d", &itm_code[i], &price[i], &stock[i]);
    }
    for(int i=0; i<m; i++)
    {
        scanf("%d %d", &requested_code[i], &requested_qnt[i]);
    }
    for(int i=0; i<n; i++)
    initial[i]=stock[i];

    for(int i=0; i<m; i++)
    {
        int k=-1;
        for(int j=0; j<n; j++)
        {
            if(requested_code[i]==itm_code[j])
            {
                k=j;
                break;
            }
        }
        
        printf("Order %d: Item %d,", i+1, requested_code[i]);
        if(k==-1)
        {
            invalid++;
            printf(" INVALID,");
            printf(" requested = %d, served = 0, gross = 0, discount = 0, bill = 0", requested_qnt[i]);
        }
        else if(stock[k]==0)
        {
            rjtd++;
            ttl_dmnd+=requested_qnt[i];
            demand[k] += requested_qnt[i];
            lst_dmnd+=demand[k];

            printf(" REJECTED,");
            printf(" requested = %d, served = 0, gross = 0, discount = 0, bill = 0", requested_qnt[i]);
        }
        else if(requested_qnt[i]>stock[k])
        {
            part++;
            ttl_dmnd+=requested_qnt[i];
            demand[k] += requested_qnt[i];
            served=stock[k];
            stock[k]=0;
            sold[k]+=served;
            ttl_sld+=served;
            gross=served*price[k];
            grs_sls+=gross;
            lst_dmnd+=requested_qnt[i]-served;
            if(served>=5)
            {
                discount=gross*0.1;
                bill=gross-discount;
            }
            else
            {
                discount=0;
                bill=gross;
            }
            ttl_dis+=discount;
            net+=bill;
            rev[k]+=bill;
            printf(" PARTIAL,");
            printf(" requested = %d, served = %d, gross = %d, discount = %d, bill = %d", requested_qnt[i], served, gross, discount, bill);
        }
        else
        {
            full++;
            ttl_dmnd+=requested_qnt[i];
            demand[k] += requested_qnt[i];
            served=requested_qnt[i];
            sold[k]+=served;
            ttl_sld+=served;
            stock[k]-=served;
            gross=served*price[k];
            grs_sls+=gross;

            if(served>=5)
            {
                discount=gross*0.1;
                bill=gross-discount;
            }
            else
            {
                discount=0;
                bill=gross;
            }
            ttl_dis+=discount;
            net+=bill;
            rev[k]+=bill;
            printf(" FULL,");
            printf(" requested = %d, served = %d, gross = %d, discount = %d, bill = %d", requested_qnt[i], requested_qnt[i], gross, discount, bill);
        }
        printf("\n");
    }
    printf("\n");
    for(int i=0; i<n; i++)
    {
        if(demand[i]>mst_dmnd)
        {
            mst_dmnd=demand[i];
            mst_dmnd_code=itm_code[i];
        }
        else if(demand[i]==mst_dmnd)
        {
            min_code=itm_code[i]<mst_dmnd_code?itm_code[i]:mst_dmnd_code;
            mst_dmnd_code=min_code;
        }
        if(sold[i]>mst_sld)
        {
            mst_sld=sold[i];
            mst_sld_code=itm_code[i];
        }
        else if(sold[i]==mst_sld)
        {
            min_code=itm_code[i]<mst_sld_code?itm_code[i]:mst_sld_code;
            mst_sld_code=min_code;
        }
        if(rev[i]>h_rev)
        {
            h_rev=rev[i];
            h_rev_code=itm_code[i];
        }
        else if(rev[i]==h_rev)
        {
            min_code=itm_code[i]<h_rev_code?itm_code[i]:h_rev_code;
            h_rev_code=min_code;
        }
    }

    for(int i=0; i<n; i++)
    {
        printf("Item %d: demand = %d, sold = %d, remaining = %d, revenue = %d", itm_code[i], demand[i], sold[i], stock[i], rev[i]);
        printf("\n");
    }
    printf("\n");
    printf("Full orders: %d\nPartial orders: %d\nRejected orders: %d\n", full, part, rjtd);
    printf("Invalid orders: %d\nTotal valid demand: %d\nTotal units sold: %d\n", invalid, ttl_dmnd, ttl_sld);
    printf("Lost demand: %d\nGross sales: %d\nTotal discount: %d\nNet revenue: %d\n", lst_dmnd, grs_sls, ttl_dis, net);
    if(mst_dmnd==0)
    printf("Most demanded item: NONE");
    else
    printf("Most demanded item: %d with %d units\n", mst_dmnd_code, mst_dmnd);
    if(mst_sld==0)
    printf("Best-selling item: NONE");
    else
    printf("Best-selling item: %d with %d units\n", mst_sld_code, mst_sld);
    if(h_rev==0)
    printf("Highest-revenue item: NONE");
    else
    printf("Highest-revenue item: %d with %d BDT\n", h_rev_code, h_rev);
    int p=1;
    printf("Items to restock:");
    for(int i=0; i<n; i++)
    {
        if(stock[i]<=initial[i]*0.2)
        {
            printf(" %d",itm_code[i]);
            p=0;
        }
    }
    if(p)
    printf(" NONE\n");
    return 0;
}
