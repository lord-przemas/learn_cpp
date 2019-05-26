#ifndef QSORT
#define QSORT

#define ASC 0x1
#define DESC 0x2

class sort {

  private:

    template <typename T>
      static unsigned qs_partition_asc(T *tab, unsigned begin, unsigned end)
      {
        unsigned i = begin;
        unsigned j = end;
        T pivot = tab[begin];

        while(true){
          while(tab[i] < pivot) i++;
          while(tab[j] > pivot) j--;

          if(i < j){
            T temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp; 
            i++;
            j--;
          }
          else
            return j;
        }
      }

    template <typename T>
      static void quicksort_asc(T *tab, unsigned begin, unsigned end)
      {
        if(begin < end){
          unsigned pindex = qs_partition_asc(tab, begin, end);
          quicksort_asc(tab, begin, pindex);
          quicksort_asc(tab, pindex + 1, end);
        }
      }

    template <typename T>
      static unsigned qs_partition_desc(T *tab, unsigned begin, unsigned end)
      {
        unsigned i = begin;
        unsigned j = end;
        T pivot = tab[begin];

        while(true){
          while(tab[i] > pivot) i++;
          while(tab[j] < pivot) j--;

          if(i < j){
            T temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp; 
            i++;
            j--;
          }
          else
            return j;
        }
      }

    template <typename T>
      static void quicksort_desc(T *tab, unsigned begin, unsigned end)
      {
        if(begin < end){
          unsigned pindex = qs_partition_desc(tab, begin, end);
          quicksort_desc(tab, begin, pindex);
          quicksort_desc(tab, pindex + 1, end);
        }
      }

    /***************************************************************************/

    template <typename T>
      static unsigned qs_partition_asc(T **tab, unsigned begin, unsigned end)
      {
        unsigned i = begin;
        unsigned j = end;
        T *pivot = tab[begin];

        while(true){
          while(*tab[i] < *pivot) i++;
          while(*tab[j] > *pivot) j--;

          if(i < j){
            T *temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp; 
            i++;
            j--;
          }
          else
            return j;
        }
      }

    template <typename T>
      static void quicksort_asc(T **tab, unsigned begin, unsigned end)
      {
        if(begin < end){
          unsigned pindex = qs_partition_asc(tab, begin, end);
          quicksort_asc(tab, begin, pindex);
          quicksort_asc(tab, pindex + 1, end);
        }
      }

    template <typename T>
      static unsigned qs_partition_desc(T **tab, unsigned begin, unsigned end)
      {
        unsigned i = begin;
        unsigned j = end;
        T *pivot = tab[begin];

        while(true){
          while(*tab[i] > *pivot) i++;
          while(*tab[j] < *pivot) j--;

          if(i < j){
            T *temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp; 
            i++;
            j--;
          }
          else
            return j;
        }
      }

    template <typename T>
      static void quicksort_desc(T **tab, unsigned begin, unsigned end)
      {
        if(begin < end){
          unsigned pindex = qs_partition_desc(tab, begin, end);
          quicksort_desc(tab, begin, pindex);
          quicksort_desc(tab, pindex + 1, end);
        }
      }

    /***************************************************************************/

  public: 

    template <typename T>
      static void quicksort(T *tab, unsigned begin, unsigned end, int order)
      {
        if(order == ASC)
          quicksort_asc(tab, begin, end - 1);
        else
          quicksort_desc(tab, begin, end - 1);
      }

    template <typename T>
      static void quicksort(T **tab, unsigned begin, unsigned end, int order)
      {
        if(order == ASC)
          quicksort_asc(tab, begin, end - 1);
        else
          quicksort_desc(tab, begin, end - 1);
      }



};

#endif //QSORT
