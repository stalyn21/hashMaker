#include <iostream>
#include "block.h"
#include "blockchain.h"
#include <ctime>

long double t0,t1;
void mine_blocks(int times);

blockchain block_chain = blockchain();

int main()
{
    std::cout << "------------------------------------------------------------------------ " << std::endl;
    std::cout << "--------------------------- Keccak algorithm --------------------------- " << std::endl;
    std::cout << "------------------------------------------------------------------------ " << std::endl;
    std::cout << "------------------------------------------------------------------------ " << std::endl;
    std::cout << std::endl;
    std::cout << "Difficulty: " << block_chain.m_difficulty << std::endl;
    Keccak keccak;
    block genesis_block = block(block_chain.size());
    genesis_block.m_hash = keccak("0");
    genesis_block.m_previous_block = &genesis_block;
    genesis_block.mine(block_chain.m_difficulty);
    block_chain.add_block(genesis_block);

    mine_blocks(15);

    //std::cout << "blockchain is " << (block_chain.is_valid() ? "valid" : "not valid") << std::endl;
}

void mine_blocks(int times)
{
    for (int i = 1; i < times+1; i++) {
        t0=clock();
        auto *current_block = new block(block_chain.size());
        current_block->m_previous_block = &block_chain.get_last();
        current_block->update();
        current_block->mine(block_chain.m_difficulty);
        block_chain.add_block(*current_block);
        
        if (i%3 ==0)
        {
            t1=clock();
            long double time = (t1-t0)/CLOCKS_PER_SEC;
            std::cout << "Execution Time: " << time << " seconds "<<std::endl;
            std::cout << std::endl;
            std::cout << "new difficulty: " << ++block_chain.m_difficulty << std::endl;
        }
    }
}
