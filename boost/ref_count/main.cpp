#include <iostream>
#include <tea/tea.h>
#include <boost/statechart/detail/counted_base.hpp>

class MediaImpl : public boost::statechart::detail::counted_base<>
{
public:
    MediaImpl(){
        add_ref();
        Debug("MediaImpl 构造，%d",ref_count());
    }
    ~MediaImpl(){
        Debug("MediaImpl 析构，%d",ref_count());
    }
};
class Media
{
public:
    Media():m_pImpl(0){

    }
    Media(MediaImpl* impl):m_pImpl(impl){

    }
    Media(const Media& other){
        Debug("Media(const Media& other)");
        if(other.m_pImpl)
            other.m_pImpl->add_ref();
        m_pImpl = other.m_pImpl;
    }
    ~Media(){
        if(m_pImpl){
            Debug("~Media()");
            if(m_pImpl->release()){
                Debug("delete m_pImpl");
                delete m_pImpl;
                m_pImpl = NULL;
            }
        }
    }
    void print(){
        Debug("ref_counted:%d",m_pImpl->ref_count());
    }
private:
    MediaImpl *m_pImpl;
};

int main()
{
    Media media(new MediaImpl());
    Media media1(media);
    media1 = media;
    media.print();
    media1.print();
    return 0;
}

