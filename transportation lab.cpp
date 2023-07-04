#include<bits/stdc++.h>
using namespace std;


int main ()
{
    //generation of decision matrix 'D'
    int criteria;
    int bfc;
    int alternative;
    cout<<"enter no. of criterians "<<endl;
    cin>>criteria;
    cout<<"Enter no. of beneficial criterians"<<endl;
    cin>>bfc;
    cout<<"enter no. of alternatives"<<endl;
    cin>>alternative;
    float D[alternative][criteria];
    cout<<"Enter values row-wise or alternative wise."<<endl;
    cout<<"NOTE: while entering the values "<<endl;
    cout<<"*** first Enter the beneficial criteria than non beneficial"<<endl;
    //step 1->creation of decision matrix;

    for (int i=0; i<alternative; i++)
    {
        for (int j=0; j<criteria; j++)
            cin>>D[i][j];
    }

//step 2-> normalisation
    float colsum;
    for (int j=0; j<criteria; j++)
    {
        //finding colsum
        colsum=0;
        for (int i=0; i<alternative; i++)
            colsum=colsum+D[i][j];
        //normalising D;
        for (int i=0; i<alternative; i++)
            D[i][j]=D[i][j]/colsum;
    }
//step 3 ->feeding the weight vector;
    float W[criteria];
    cout<<"enter weight for corresponding criteria carefully"<<endl;
    for (int i=0; i<criteria; i++)
    {
        cin>>W[i];
    }
//step 4 -> creating weighted decision matrix;
    for (int i=0; i<alternative; i++)
    {
        for (int j=0; j<criteria; j++)
        {
            D[i][j]=(D[i][j])*(W[j]);
        }
    }

//step 5-> Pi ~ summation over beneficial criteria.
    float Pi[alternative]= {0};
    for (int i=0; i<alternative; i++)
        for (int j=0; j<bfc; j++)
        {
            Pi[i]+=D[i][j];
        }
// step 6-> Ri~summation over the non-beneficial criteria.

    float Ri[alternative]= {0};
    for (int i=0; i<alternative; i++)
        for (int j=bfc; j<criteria; j++)
        {
            Ri[i]+=D[i][j];
        }
//step 7->finding the minimum of Ri
    float Rimin=INT_MAX;
    for (int i=0; i<alternative; i++)
    {
        if (Rimin>Ri[i])
            Rimin=Ri[i];
    }
    /*step 8->finding Qi values;
       steps (a)finding summation Ri;
             (b)finding summation Rimin/Ri=ratiosum (say);
    */
//(a)
    float Risum=0;
    for (int i=0; i<alternative; i++)
        Risum=Risum+Ri[i];

//(b)
    float ratiosum=0;
    for (int i=0; i<alternative; i++)
        ratiosum=ratiosum+(Rimin)/(Ri[i]);


//Qi  value
    float Qi[alternative];
    for (int i=0; i<alternative; i++)
    {
        Qi[i]=Pi[i]+((Rimin*Risum)/(Ri[i]*ratiosum));
    }

//step 9-> finding Qimax;
    float Qimax=INT_MIN;
    for (int i=0; i<alternative ; i++)
    {
        if (Qimax<Qi[i])
            Qimax=Qi[i];
    }
//step 10->converting Qi into percentage//utility percentage;
    for (int i=0; i<alternative; i++)
    {
        Qi[i]=((Qi[i]/Qimax)*100);
    }
    cout<<endl;
//printing performance values
    cout<<"utility index of respective alternatives"<<endl;
        for (int i=0; i<alternative ; i++)
    {
        cout<<Qi[i]<<endl;
    }
    cout<<endl;
    int ans;
//step 11->determination of the rank vector;
    int ranks[alternative];
    priority_queue<float>pq;
    for (int i=0; i<alternative; i++)
    {
        pq.push(Qi[i]);
    }
    int r=1;
    for (int i=0; i<alternative; i++)
    {
        float top=pq.top();
        pq.pop();
        for (int i=0; i<alternative ; i++)
        {
            if (top==Qi[i])
            {
                ranks[i]=r;
                if (r==1)
                    ans=i+1;
                r++;
            }
        }
    }
//printing ranks;
    cout<<endl;
    cout<<"ranks of respective alternative"<<endl;
        for (int i=0; i<alternative; i++)
    {
        cout<<ranks[i]<<endl;
    }
    cout<<endl<<ans<<" th alternative is the best choice"<<endl;

    return 0;
}
