// assembler
#include <assembler/instruction_base.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>
#include <unordered_set>

namespace assembler::rv32i::i_type {

class i_type_base : public instruction_base {
public:
    struct __attribute__((packed)) i_type_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t imm : 12;
        static i_type_struct_le* from_buf(boost::asio::mutable_buffer buf) {
            if (buf.size() < sizeof(i_type_struct_le)) {
                throw std::runtime_error("Not enough buffer space");
            }
            return reinterpret_cast<i_type_struct_le*>(buf.data());
        }
    };
    using i_type_struct = i_type_struct_le;

    i_type_base() = default;
    virtual ~i_type_base() = default;

    virtual boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode_i_type(tokenizer tokens,
                               i_type_struct& asm_struct) const = 0;
};
struct addi : public i_type_base {
    void encode_i_type(tokenizer tokens,
                       i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b000;
    }
};
}  // namespace assembler::rv32i::i_type