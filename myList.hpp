namespace gamingList{
    //legacy code don't remove
    int abs(int num){
        return (num > 0)?num:-num;
    }
    int distance(int num1,int num2){
        return abs(num2-num1);
    }

    template <typename T>
    struct node
    {
        T data;
        node<T>* next;
        node<T>* prev;
    };
    
    template <class T>
    class list{
    private:
        node<T>* head;
        int total = 0;
        node<T>* tail;
        
        //caches the previous node visited so that when looping through sequentially the code is significantly faster
        node<T>* cache;
        int cachePos = -1;

        void resetCache(){
            cachePos = -1;
        }

        node<T>* GetNodeAtIndex(int index){
            //edge cases == speed
            if(index == 0){return this->head;}  
            if(index == this->total - 1){return this->tail;}    
            //ensure the cach is not reset
            if(cachePos < 0){cachePos = 0;cache = head;}

            bool Forward; //direction of loop
            int i;  //index being used while looping
            node<T>* current; //current pointer being used while looping
            
            //finds weather it would be faster to start at the head,tail or cach
            if(distance(0,index) < distance(cachePos,index)
            ||distance(total - 1,index) < distance(cachePos,index)
            ){
                if(index < (this->total/ 2)){//starting at head
                    current = head;
                    i = 0;
                    Forward = true;
                }

                else{//starting at tail
                    current = tail;
                    i = this->len() - 1;
                    Forward = false; 

                }
            } 
            else{//starting at cach
                current = cache;
                i = cachePos;
                Forward = (index - cachePos > 0);
            }


            //start the loop
            do{
                if(i == index){break;}//found the item
                if(Forward){
                    current = current->next;
                    i++;
                }
                else{
                    current = current->prev;
                    i--; 
                }
            }while(current!=tail && current != head);//if its looking for an item outsied of range it will return the closest

            cachePos = index;    //edit the cach
            cache = current;
            return current;

        }



    public:
        int len(){
            return this->total;
        }

        void append(T newdata){
            if(total == 0){
                this->head = new node<T>;
                this->head->data = newdata;
                this->tail = this->head;
                total++;
            }

            else{
                this->tail->next = new node<T>;
                this->tail->next->prev = this->tail;
                this->tail = tail->next;
                this->tail->data = newdata;
                total++;
            }
        }


        T get(int index){
            node<int>* temporary =  GetNodeAtIndex(index);
            return temporary->data;
        }

        
        //remove // return true if pass return false if fail;
        bool remove(int index){
            if(index < 0 || index >= this->total){return false;}
            node<T>* current = GetNodeAtIndex(index); 
            if(cachePos == index){
                cache = cache->prev;
                cachePos--;
            }
            if(current == head){
                this->head = current->next;
                delete(current);
            }
            else if(current == tail){
                this->tail = current->prev;
                delete(current);
            }
            else{
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete(current);
            }

            if(cachePos > index){
                cachePos--;
            }

            this->total--;
            return true;
        }

        void insert(T newData,int index){
            if(index == this->total){
                this->append(newData);
                return;
            }

            node<T>* current = GetNodeAtIndex(index);
            node<T>* adding = new node<T>;
            adding->data = newData;

            if(cachePos == index){
                cache = cache->prev;
                cachePos--;
            }

            if(current == this->head){
                current->prev = adding;
                adding->next = current;
                this->head = adding;                

                this->total++;

            }else{
                adding->prev = current->prev;
                adding->next  = current;

                current->prev->next = adding;
                current->prev = adding;
                
                this->total++;
            }
            if(cachePos > index){cachePos++;}

        }




		void sort(bool backward = false) {
			for (int i = 1; i < this->total; i++) {
				T originalData = this->get(i);
				for (int j = i - 1; j >= 0; j--) {
					T Jdata = this->get(j);
					if (!backward) {
						if (originalData > Jdata) {
							//swapToHere;
							this->remove(i);
							this->insert(originalData, j + 1);
							j = -1; //stop the looping
						}
						else if (j == 0) {
							this->remove(i);
							this->prepend(originalData);
						}
					}
					else {
						if (originalData < Jdata) {
							//swapToHere;
							this->remove(i);
							this->insert(originalData, j + 1);
							j = -1; //stop the looping
						}
						else if (j == 0) {
							this->remove(i);
							this->prepend(originalData);
						}
					}
				}

			}

		}
        void pop_front(){
            this->remove(0);
        }
        void pop_back(){
            this->remove(this->total-1);
        }

        void prepend(T newdata){
            this->insert(newdata,0);
        }

        void push_front(T newdata){
            this->prepend(newdata);
        }

        ~list(){
            while(remove(0));
        }

    };
};