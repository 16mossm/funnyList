namespace gamingList{

    bool withinRange(int value1,int value2,int range){
        if(value1 >= value2 - range && value1 <= value2 + range){return true;}
        return false;
    }
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
        
        //for performance
        node<T>* cach;
        int cachPos = -1;

        void resetCach(){
            cachPos = -1;

        }


        node<T>* GetNodeAtIndex(int index){
            //edge cases == speed
            if(index == 0){return this->head;}  
            if(index == this->total - 1){return this->tail;}    
            //ensure the cach is not reset
            if(cachPos < 0){cachPos = 0;cach = head;}

            //direction of loop
            bool Forward;
            //index being used while looping
            int i;
            //current pointer being used while looping
            node<T>* current;
            
            //finds weather it would be faster to start at the head,tail or cach
            if(distance(0,index) < distance(cachPos,index)
            ||distance(total - 1,index) < distance(cachPos,index)
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
                current = cach;
                i = cachPos;
                Forward = (index - cachPos > 0);
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

            cachPos = index;    //edit the cach
            cach = current;
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
            
            if(current == head){
                this->head = current->next;
                delete(current);
                total--;
                return true;
            }
            if(current == tail){
                this->tail = current->prev;
                delete(current);
                total--;
                return true;
            }

            node<int>* previous = GetNodeAtIndex(index - 1); 
            node<int>* after = GetNodeAtIndex(index + 1); 

            previous->next = after;
            after->prev = previous;
            


            resetCach();
            this->total--;
            delete(current);
            return true;
        }

        ~list(){
            while(remove(0));
        }

    //yep
        void prepend(T newdata){
            this->insert(newdata,0);
        }

        void push_front(T newdata){
            this->prepend(newdata);
        }



        


        void insert(T newData,int index){
            node<T>* current = GetNodeAtIndex(index);
            std::cout << "hovgsoihgj;hgsdhiog: " << current->data <<std::endl;
            if(current == this->tail){
                this->append(newData);
                resetCach();
                return;
            }

            node<T>* adding = new node<T>;
            adding->data = newData;

            if(current == this->head){
                current->prev = adding;
                adding->next = current;
                this->head = adding;                

                this->total++;
                
                resetCach();
                return;
            }
            
            adding->prev = current->prev;
            adding->next  = current;

            current->prev->next = adding;
            current->prev = adding;
            
            this->total++;
            resetCach();
        }


        void pop_front(){
            this->remove(0);
        }
        void pop_back(){
            this->remove(this->total-1);
        }


    };
};